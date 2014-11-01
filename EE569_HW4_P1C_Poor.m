%%%%%%%%%%%%%%%%%%%%
%EE 569 Homework #4
%Date:			December 1, 2013
%Name:			Shreyansh Dnyanesh Daga
%ID:			6375-3348-33	
%Email:			sdaga@usc.edu
%Compiled and build on 	Matlab R2013a
%OS: Windows 8
%File: EE569_HW4_P1B.m
%%%%%%%%%%%%%%%%%%%%%%%%


movieObj1 = VideoWriter('EE569_HW4_P1C_Poor.avi');
movieObj1.FrameRate = 5;
open(movieObj1);


% for i = 1:3
%     str = 'Result_Drew_100.raw';
%     C = ReadRGBRaw(str,350,300);
%     imshow(C);
%     frame = getframe;
%     writeVideo(movieObj1,frame);
% end
    
for i = 1:21
    str = int2str(i-1);
    szName = strcat('Result_BW_7Point_',str,'.raw');
    
    C = ReadRGBRaw(szName,400,400);   
    imshow(C);
    frame = getframe;
    writeVideo(movieObj1,frame);
end

% for i = 1:2
%     str = 'Result_Drew.raw';
%     C = ReadRGBRaw(str,350,300);
%     imshow(C);
%     frame = getframe;
%     writeVideo(movieObj1,frame);
% end

close(movieObj1);
disp(movieObj1);