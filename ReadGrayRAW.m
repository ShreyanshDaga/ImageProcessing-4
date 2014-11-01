%%%%%%%%%%%%%%%%%%%%
%EE 569 Homework #3
%Date:			November 3, 2013
%Name:			Shreyansh Dnyanesh Daga
%ID:			6375-3348-33	
%Email:			sdaga@usc.edu
%Compiled and build on 	Matlab R2013a
%OS: Windows 8
%File: ReadRGBRaw.m
% It reads RGB raw file in matlab
%%%%%%%%%%%%%%%%%%%%%%%%

function C = ReadGrayRAW(szFileName,iRows,iCols)

id = fopen(szFileName, 'r');

if(id == -1)
    disp('Can Not Open File !!');
    pause;
end

x = fread(id,inf,'uint8')'; 
x = x/255;

fclose(id);

width = iCols;
height = iRows;

N = width*height;

ind1 = 1:1:N;

Ir = x(ind1);

Ir1 = reshape(Ir,width,height);

figure(1); clf;
C = zeros(height,width,1);

C(:,:,1)=Ir1';

clear x;
clear id;
imagesc(C);