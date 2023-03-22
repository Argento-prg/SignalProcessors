Ic= imread('Image2.bmp');
Ic = Ic(:,:,1);
mn=size(Ic);
fid = fopen('Image2.dat','w');
fprintf(fid, '1651 2 0 0 0\r\n');
Ic=double(Ic);%преобразуем формат данных изображения
for i=1:8:mn(1), %в цикле по строкам изображения
for j=1:8:mn(2), %в цикле по столбцам изображения
block = Ic(i:i+7,j:j+7);
for v = 1:8
for g=1:8
fprintf(fid, '%i\r\n', block(v,g));%выводим значение пикселя
end
end
end
end
fclose(fid);% закрываем файл