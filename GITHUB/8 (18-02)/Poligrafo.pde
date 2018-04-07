import processing.serial.*;

Serial Port;
boolean found;
IntList buf;
int L_Screen = 900, H_Screen = 750, estado = 1, lastx = 0, lasty = L_Screen, posx = 0, posy, increm = 2, i = 0, j = 0; 
int a = 16, b = 16, c = 16, sub_a = 8, sub_b = 8, sub_c = 8;
byte byte1, byte2;
//   ASCII: + 43, - 45

void setup(){
    size(900, 750);
    println(Serial.list());
    Port = new Serial(this, Serial.list()[0], 115200);
    Port.buffer(3);
    buf = new IntList();
    background(255);
}

void draw(){
    
    grid();
    
    if(buf.size()>=4){
      if(posx < L_Screen){
        posy = buf.remove(0);
        line(lastx, lasty, posx, posy);
        lastx = posx;
        lasty = posy;
        posx += increm;
      } else {
        posx = 0;
        lastx = 0;
        lasty= 620;
        background(255);
        buf.clear();
      }
    }
}

void serialEvent(Serial Port){
  byte[] in = new byte[3];
  Port.readBytes(in);
  
  for(int i=0;i<3;i++){
    if(in[i] == -14){
      found = true;
      //estado =1; 
    } 
    if(found){
      switch (estado){
        //case 1:
          //estado = 2;
          //break;
        
        //case 2:
        case 1:
          byte1 = in[i];
          // decodificar digitales
          //estado = 3;
          estado=2;
          //println(hex(con1));
          break;
        
        //case 3:
        case 2:
          byte2 = in[i];
          //println(hex(con2));
          buf.append(decode(byte1,byte2)); // Valores en la lista.
          
          estado = 1;
          break;
      
      }    
    }

  }

  
  //println(in);
}

void grid()
{
   // Channel A
   for(j = 0; j <= 112; j += a)
   {
      for(i = 0; i <= 816; i += a)
      {
         rect(32 + i, 50 + j, a, a);
      }   
   }
   if(a == 32)
   {
      
   }
   
   // Channel B
   for(j = 0; j <= 112; j += b)
   {
      for(i = 0; i <= 816; i += b)
      {
         rect(32 + i, 228 + j, b, b);
      }   
   }
   
   // Channel C
   for(j = 0; j <= 112; j += c)
   {
      for(i = 0; i <= 816; i += c)
      {
         rect(32 + i, 406 + j, c, c);
      }   
   }
   
}

void keyPressed() 
{
  // Control del eje vertical (canal A)
  
  if (key == '1' && a < 64)
  {
     a *= 2;
  }

  if (key == '2' && a > 16) 
  {
      a /= 2;
  }

  // Control del eje vertical (canal B)
  
  if (key == '3' && b < 64)
  {
     b *= 2;
  }

  if (key == '4' && b > 16) 
  {
     b /= 2;
  }
  
  if (key == '5' && c < 64)
  {
     c *= 2;
  }

  if (key == '6' && c > 16) 
  {
      c /= 2;
  }
  
  
}

int decode(byte con1, byte con2){
  int aux1, aux2, aux3, aux4, code;
  
  aux1 = con1 & 0x1F;
  aux2 = con2 << 1;
  aux3 = aux1 << 8;
  aux4 = aux2 & 0x00FF;
  aux4 = aux3 | aux4;
  code = aux4 >> 1;
  
  code = (int)map(code,0,4096,620,0);
  //println(code);
  return code;

}