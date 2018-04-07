import processing.serial.*;

Serial Port;
boolean found;
IntList buf;
int estado = 1, lastx = 0, lasty = 850, posx = 60, posy, increm = 40, i=0, j=0, k=0;
int a = 20, b = 20, c = 20, sub_a = 8, sub_b = 8, sub_c = 8;
int offset_a = 50;
byte byte1, byte2;


void setup(){
    size(1000,850);
    println(Serial.list());
    Port = new Serial(this, Serial.list()[0], 115200);
    Port.buffer(3);
    buf = new IntList();
    background(0);
    grid();
    
}

void draw(){
    if(buf.size()>=80){
      if(posx < 980){
        posy = buf.remove(0);
        line(lastx, lasty, posx, posy);
        lastx = posx;
        lasty = posy;
        posx += increm;
       
      } else {
        posx = 60;
        lastx = 0;
        lasty= 850;
        background(0);
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
   for(j = 0; j <= 230; j += a)
   {
      for(i = 0; i <= 880; i += a)
      {
        
         rect(60 + i, 50 + j, a, a);
         
         
              
      }   
   }
   
   //fill(0);
   textSize(8);
   text("50,00°", 30, 55);
   //text("2,75", 30, 70);
  
   textSize(8);
   text("41,67°", 30, 95);
   //text("2,25", 30, 110);
   
   textSize(8);
   text("33,33°", 30, 135);
   //text("1,75", 30, 150);
   
   textSize(8);
   text("25,00°", 30, 175);
   //text("1,25", 30, 190);
   
   textSize(8);
   text("16,67°", 30, 215);
   //text("0,75", 30, 230);
   
   textSize(8);
   text("8,33°", 30, 255);
   //text("0,25", 30, 270);
   
   textSize(8);
   text("0,00°", 30, 295);
   
   /*
   textSize(20);
   text("Sensor de temperatura LM35", 400, 20);
   */
   
   
   /*
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
   */
   
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
  
  code = (int)map(code,0,1550,290,200);

  return code;

}