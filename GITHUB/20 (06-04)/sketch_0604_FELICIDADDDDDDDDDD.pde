import processing.serial.*;

Serial Port;
boolean found;
IntList buf, buf2, buf3;
int estado = 1, lastx = 60, lasty = 260, posx = 60, posy, increm = 5, i=0, j=0, k=0;
int lastx2 = 60, lasty2 = 480, posx2 = 60, posy2; //290
int lastx3=60, lasty3=700, posx3=60, posy3;
int a = 20, b = 20, c = 20, sub_a = 8, sub_b = 8, sub_c = 8;
int offset_a = 50;
int offset_b = 280;
int D1;
int D2;
byte byte1, byte2, byte3, byte4, byte5, byte6;
color azul=color(0,0,255), rojo=color(255,0,0), verde=color(0,255,0);



void setup(){
    size(1000,1150);
    println(Serial.list());
    Port = new Serial(this, Serial.list()[0], 115200);
    Port.buffer(7);
    buf = new IntList();
    buf2= new IntList();
    buf3= new IntList();
    
    background(0);    
    grid1();
    grid2();
    grid3();
    //fill(azul);
    //ellipse(440,450,70,70);  
 
    
        
    
}

void draw(){
  
  stroke(verde);
  fill(verde);
  ellipse(800,900,10,10);
  
  stroke(azul);
  fill(azul);
  ellipse(800,920,10,10);
  
  stroke(rojo);
  fill(rojo);
  ellipse(800,940,10,10);
 
  
   if(D2==0x20)
   {
         stroke(verde);
         fill(verde);
         ellipse(750,900,40,40);
    }
  
    if(buf3.size()>=5 || buf3.size()>=5 || buf3.size()>=5)
    {
       if(posx3 < 960 || posx2 < 960 || posx < 960)
       {
          // Channel 1
          posy = buf.remove(0);
          stroke(azul);
          line(lastx, lasty, posx, posy);
          lastx = posx;
          lasty = posy;
          posx += increm;
          println(posy);
          
          // Channel 2
          posy2 = buf2.remove(0);
          stroke(rojo);
          line(lastx2, lasty2, posx2, posy2);
          lastx2 = posx2;
          lasty2 = posy2;
          posx2 += increm;
          
          // Channel 3
          posy3 = buf3.remove(0);
          stroke(verde);
          line(lastx3, lasty3, posx3, posy3);
          lastx3 = posx3;
          lasty3 = posy3;
          posx3 += increm;
          
          
        
          if(D2==0x20)
          {
              stroke(verde);
              fill(verde);
              ellipse(750,900,40,40);
          }
          else
          {  
             //fill(verde);
             //ellipse(750,20,40,40);
              if(D1==0x40)
              {
                stroke(rojo);
                fill(rojo);
                ellipse(750,900,40,40);
              }
             else
             {
                stroke(azul);
                fill(azul);
                ellipse(750,900,40,40);
            }  
         }
         buf3.clear();
        buf2.clear();
        buf.clear();
       } 
       else 
       {        
          posx = 60;
          lastx = 60;
          lasty= 260;
          posx2 = 60;//290
          lastx2 = 60;//290
          lasty2= 480;
           posx3 = 60;//290
          lastx3 = 60;//290
          lasty3= 700;
          background(0);
          grid1();
          grid2();
          grid3();
        
          if(D2==0x20)
          {
              stroke(verde);
              fill(verde);
              ellipse(750,900,40,40);
          }
          else
          { 
            //fill(verde);
            //ellipse(750,20,40,40);
                  if(D1==0x40)
                  {
                  stroke(rojo);
                  fill(rojo);
                  ellipse(750,900,40,40);
                  }
                 else
                 {
                    stroke(azul);
                    fill(azul);
                    ellipse(750,900,40,40);
                 }  
          }
        //fill(azul);
        //ellipse(440,450,70,70);
        buf3.clear();
        buf2.clear();
        buf.clear();
        
      }
      
    }
    
 
}
      
 
   
    

void serialEvent(Serial Port){
  byte[] in = new byte[7];
  Port.readBytes(in);
  
  for(int i=0;i<7;i++){
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
          D2=digital_2(byte1);
          //D2=0x40;
          estado = 3;
          //estado=2;
          //println(hex(D1));
          break;
        
        case 3:
       
          byte2 = in[i];
          //println(hex(byte2));
          
         estado=4;
         // estado = 4;
          break;
           
           //SEPARAR LOS CASE CON UNA MAQUINA DE ESTADO M=1
          
          case 4:
       
          byte3 = in[i];
          // decodificar digitales
          //D1= digital_1(byte1);
          //D2=digital_2(byte1);
          //D2=0x40;
          estado = 5;
          //estado=2;
          //println(hex(D1));
          break;
          
                    
          case 5:
       
           byte4 = in[i];
          //println(hex(byte2));
          
          estado = 6;
          break;
          
          
          case 6:
       
          byte5 = in[i];
          // decodificar digitales
          //D1= digital_1(byte1);
          //D2=digital_2(byte1);
          //D2=0x40;
          estado = 7;
          //estado=2;
          //println(hex(D1));
          break;
          
                    
          case 7:
       
           byte6 = in[i];
          //println(hex(byte2));
          buf.append(decode(byte1,byte2,offset_a)); // Valores en la lista.
          buf2.append(decode2(byte3,byte4,offset_a)); // Valores en la lista.
          buf3.append(decode3(byte5,byte6,offset_a)); // Valores en la lista.
          estado = 1;
          found=false;
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
         stroke(0);
         rect(60 + i, 50 + j, a, a);
         
         
              
      }   
   }
 
   textSize(12);
   text("Sensor de respiración", 420, 45);
 /*
   //fill(0);
   textSize(8);
   text("50,00°", 30, 55);
   //text("2,75", 30, 70);
  
   textSize(8);
   text("41,67°", 30, 95);
   //text("2,25", 30, 110);
  */ 
   textSize(8);
   text("40,00°", 30, 55);
   //text("1,75", 30, 150);
   
   textSize(8);
   text("30,00°", 30, 115);
   //text("1,25", 30, 190);
   
   textSize(8);
   text("20,00°", 30, 175);
   //text("0,75", 30, 230);
   
   textSize(8);
   text("10,00°", 30, 235);
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
         stroke(0);
         rect(60 + i, 50 + j, a, a);
         
         
              
      }   
   }
   
   
   textSize(12);
   text("Sensor de ritmo cardiaco", 420, 325);
   
   //fill(0);
   textSize(8);
   text("3.00V", 30, 335);
   //text("2,75", 30, 70);
 
   textSize(8);
   text("2.50V", 30, 375);
   //text("2,25", 30, 110);
   
   textSize(8);
   text("2.00V", 30, 415);
   //text("1,75", 30, 150);
   
   textSize(8);
   text("1.50V", 30, 455);
   //text("1,25", 30, 190);
   
   textSize(8);
   text("1.00V", 30, 495);
   //text("0,75", 30, 230);
   
   textSize(8);
   text("0.50V", 30, 535);
   //text("0,25", 30, 270);
   
   textSize(8);
   text("0.00V", 30, 575);
 
 
  
  
  }
    
  
  //Tercer canal analógico
  
  void grid3()
{
   
   // Channel A
   for(j = 560; j <= 790; j += a)
   {
      for(i = 0; i <= 880; i += a)
      {
         fill(255);
         stroke(0);
         rect(60 + i, 50 + j, a, a);
         
         
              
      }   
   }


   textSize(12);
   text("Resistencia galvánica de la piel", 420, 605);
   
   //fill(0);
   textSize(8);
   text("3.00V", 30, 615);
   //text("2,75", 30, 70);
 
   textSize(8);
   text("2.50V", 30, 655);
   //text("2,25", 30, 110);
   
   textSize(8);
   text("2.00V", 30, 695);
   //text("1,75", 30, 150);
   
   textSize(8);
   text("1.50V", 30, 735);
   //text("1,25", 30, 190);
   
   textSize(8);
   text("1.00V", 30, 775);
   //text("0,75", 30, 230);
   
   textSize(8);
   text("0.50V", 30, 815);
   //text("0,25", 30, 270);
   
   textSize(8);
   text("0.00V", 30, 855); 
 
  textSize(10);
  text("En espera de respuesta", 820, 900);
  
  textSize(10);
  text("NO", 820, 920);
  
  textSize(10);
  text("SI", 820, 940);
  
 
  
  
  }
  
  


/*
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
*/

int decode(byte con1, byte con2, int offset_a){
  int aux1, aux2, aux3, aux4, code;
  
  aux1 = con1 & 0x1F;
  aux2 = con2 << 1;
  aux3 = aux1 << 8;
  aux4 = aux2 & 0x00FF;
  aux4 = aux3 | aux4;
  code = aux4 >> 1;
  
  
  code = (int)map(code,0,100,330,200);

  return code;

}



int decode2(byte con1, byte con2, int offset_a){
  int aux1, aux2, aux3, aux4, code;
  
  aux1 = con1 & 0x1F;
  aux2 = con2 << 1;
  aux3 = aux1 << 8;
  aux4 = aux2 & 0x00FF;
  aux4 = aux3 | aux4;
  code = aux4 >> 1;
  
  
  code = (int)map(code,0,380,580,200);

  return code;

}


int decode3(byte con1, byte con2, int offset_a){
  int aux1, aux2, aux3, aux4, code;
  
  aux1 = con1 & 0x1F;
  aux2 = con2 << 1;
  aux3 = aux1 << 8;
  aux4 = aux2 & 0x00FF;
  aux4 = aux3 | aux4;
  code = aux4 >> 1;
  
  
  code = (int)map(code,0,800,825,200);

  return code;

}



int digital_1(byte con1){
  int aux1; 
  aux1=con1 & 0x40;
  
  return aux1;

}
int digital_2(byte con1){
  int aux1; 
  aux1=con1 & 0x20;
  
  return aux1;

}