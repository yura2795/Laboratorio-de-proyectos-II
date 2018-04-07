import processing.serial.*;

Serial Port;
boolean found;
IntList buf;
int estado = 1, lastx = 0, lasty = 620, posx = 0, posy, increm = 4; 
byte con1, con2;
//   ASCII: + 43, - 45

void setup(){
    size(840,620);
    println(Serial.list());
    Port = new Serial(this, Serial.list()[0], 115200);
    Port.buffer(3);
    buf = new IntList();
    background(255);
}

void draw(){
    if(buf.size()>=20){
      if(posx < 840){
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
    } 
    if(found){
      switch (estado){
        case 1:
          estado = 2;
          break;
        
        case 2: 
          con1 = in[i];
          // decodificar digitales
          estado = 3;
          //println(hex(con1));
          break;
        
        case 3:
          con2 = in[i];
          //println(hex(con2));
          buf.append(decode(con1,con2)); // Valores en la lista.
          
          estado = 1;
          break;
      
      }    
    }

  }

  
  //println(in);
}

void keyPressed() {
  if (key == '+') {
    if(increm < 100){
      increm += 2;
    }
  }
  if (key == '-') {
    if(increm > 0){
      increm -= 2;
    }
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