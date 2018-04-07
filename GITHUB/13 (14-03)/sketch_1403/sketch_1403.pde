import processing.serial.*;

Serial Port;
boolean found;
IntList buf;
int estado = 1, lastx = 60, lasty = 250, posx = 60, posy, increm = 40, i=0, j=0, k=0;
int a = 20, b = 20, c = 20, sub_a = 8, sub_b = 8, sub_c = 8;
int offset_a = 50;
int offset_b = 280;
int D1;
//int D2;
byte byte1, byte2;
color azul=color(0,0,255), rojo=color(255,0,0);


void setup(){
    size(1000,850);
    println(Serial.list());
    Port = new Serial(this, Serial.list()[0], 115200);
    Port.buffer(3);
    buf = new IntList();
    
    background(0);    
    grid1();
    grid2();
    //fill(azul);
    //ellipse(440,450,70,70);
    
   
    
        
    
}

void draw(){
  
    if(buf.size()>=80){
       if(posx < 980){
        posy = buf.remove(0);
        line(lastx, lasty, posx, posy);
        lastx = posx;
        lasty = posy;
        posx += increm;
        
          if(D1==0x40){
            fill(rojo);
            ellipse(750,20,40,40);
             }
          else{
            fill(azul);
            ellipse(750,20,40,40);
            }  
          
      } 
       else {
        
        posx = 60;
        lastx = 60;
        lasty= 250;
        background(0);
        grid1();
        grid2();
           if(D1==0x40){
              fill(rojo);
              ellipse(750,20,40,40);
              }
           else{
              fill(azul);
              ellipse(750,20,40,40);
              }  
        
        //fill(azul);
        //ellipse(440,450,70,70);
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
          D1= digital_1(byte1);
          //D2=0x00;
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

//Primer canal analógico

void grid1()
{
   
   // Channel A
   for(j = 0; j <= 230; j += a)
   {
      for(i = 0; i <= 880; i += a)
      {
         fill(255);        
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
} 
   
//Segundo canal analógico

void grid2()
{
   
   // Channel A
   for(j = 280; j <= 510; j += a)
   {
      for(i = 0; i <= 880; i += a)
      {
         fill(255);
         rect(60 + i, 50 + j, a, a);
         
         
              
      }   
   }
   
   //fill(0);
   textSize(8);
   text("3.00V", 30, 335);
   //text("2,75", 30, 70);
 /* 
   textSize(8);
   text("2.58V", 30, 95);
   //text("2,25", 30, 110);
   
   textSize(8);
   text("2.16V", 30, 135);
   //text("1,75", 30, 150);
   
   textSize(8);
   text("1.74V", 30, 175);
   //text("1,25", 30, 190);
   
   textSize(8);
   text("1.32V", 30, 215);
   //text("0,75", 30, 230);
   
   textSize(8);
   text("0.90V", 30, 255);
   //text("0,25", 30, 270);
   
   textSize(8);
   text("0.42V", 30, 295);
 
 
  
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


int digital_1(byte con1){
  int aux1; 
  aux1=con1 & 0x40;
  
  return aux1;

}