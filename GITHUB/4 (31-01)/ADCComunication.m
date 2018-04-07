function [sen] = ADCComunication()

clc
clear all

port = serial('COM4');

set(port,'BaudRate',115200);

fopen(port);

sen=fgetl(port);
sen=unicode2native(sen);

display(sen)

fprintf(port,'*IDN?')
out = fscanf(port);

fclose(port)
delete(port)
clear port

end
