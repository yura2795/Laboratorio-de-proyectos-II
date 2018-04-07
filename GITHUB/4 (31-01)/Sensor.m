clc
clear all
close all

sensor = ADCComunication();
isensor = uint16(sensor);

k = 1;
n=1;

% for i = 2:3:length(isensor)-1
%     % W && 0x1F
%     a = bitand(isensor(i), 31);
% 
%     % W << 1 
%     b = bitsll(isensor(i+1), 1);
% 
%     % W << 8
%     c = bitsll(a,8);
% 
%     % W && 0xFF
%     d = bitand(b,255);
% 
%     % c || d
%     d = bitor(c,d);
% 
%     sd(k) = bitsrl(d,1);
%     
%     k = k+1;
% end


for i = 1:2:length(isensor)-1
    if(isensor(i) < 16)
        sd(n) = (isensor(i)*255) + isensor(i+1);
    else
        sd(n) = (isensor(i+1)*255) + isensor(i);
    end
    
    n = n+1;
 end

sd = double(sd);
a=3/4095;

for j = 1:length(sd)
    convert(j) = sd(j) .* a;
end   

t=0:1:length(convert)-1;

stem(t,convert); title('Medición'); xlabel('Tiempo'); ylabel('Voltaje');
