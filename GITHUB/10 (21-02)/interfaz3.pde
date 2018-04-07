import processing.serial.*;

Serial Port;
boolean found;
IntList buf;
int estado = 1, lastx = 0, lasty = 850, posx = 0, posy, increm = 40, i=0, j=0;
int a = 20, b = 20, c = 20, sub_a = 8, sub_b = 8, sub_c = 8;
int offset_a = 50;
byte byte1, byte2;


void setup(){
    size(1000,850);
    println(Serial.list());
    Port = new Serial(this, Serial.list()[0], 115200);
    Port.buffer(3);
    buf = new IntList();
    background(255);
    grid();
}

void draw(){
    if(buf.size()>=80){
      if(posx < 1000){
        posy = buf.remove(0);
        line(lastx, lasty, posx, posy);
        lastx = posx;
        lasty = posy;
        posx += increm;
       
      } else {
        posx = 0;
        lastx = 0;
        lasty= 850;
        background(255);
        grid();
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
      
    } 
    if(found){
      switch (estado){
        case 1:
          estado = 2;
          break;
        
        case 2:
        
          byte1 = in[i];
          // decodificar digitales
          estado = 3;
          //estado=2;
          println(hex(byte1));
          break;
        
        case 3:
       
          byte2 = in[i];
          println(hex(byte2));
          buf.append(decode(byte1,byte2,offset_a)); // Valores en la lista.
          
          estado = 1;
          break;
      
      }    
    }

  }

  

}

void grid()
{
   // Channel A
   for(j = 0; j <= 190; j += a)
   {
      for(i = 0; i <= 880; i += a)
      {
         rect(60 + i, 50 + j, a, a);
      }   
   }
   
   text("33333333333333", 50, 100);
   /*
   for(i = 0; i <= 3; i += 0.3)
   {
       text(char(i), 50, 50 + j);
       j += 50;
   }
   */
   // Channel B
   for(j = 0; j <= 190; j += b)
   {
      for(i = 0; i <= 880; i += b)
      {
         rect(60 + i, 300 + j, b, b);
      }   
   }
   
   // Channel C
   for(j = 0; j <= 190; j += c)
   {
      for(i = 0; i <= 880; i += c)
      {
         rect(60 + i, 550 + j, c, c);
      }   
   }
   
}


void keyPressed() 
{
  if (key == '+' && posx < 1000 && increm < 100)
  {
     increm += 2;
  }

 
  if (key == '-' && posx > 0 && increm > 0) 
  {
      increm -= 2;
  }
  
}

int decode(byte con1, byte con2, int offset_a){
  int aux1, aux2, aux3, aux4, code;
  
  aux1 = con1 & 0x1F;
  aux2 = con2 << 1;
  aux3 = aux1 << 8;
  aux4 = aux2 & 0x00FF;
  aux4 = aux3 | aux4;
  code = aux4 >> 1;
  
  code = (int)map(code,0,4096,400,200);

  return code;

}