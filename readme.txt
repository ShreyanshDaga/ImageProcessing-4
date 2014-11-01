IDE Used: Visual Studio 2012 Professional
OS: Widows 8/ Windows 7
Language: C++

The source code contains the following files

*Headers Files:
HW_3.h				--COntains prototype of genera fucntions used
Pixel.h				--Contains decln of Pixel class and Point Class	
Image.h				--Contains decln of Image class
Histogram.h			--Contains decln of Histogram class
Matrix.h			--Contains decln of Matrix Class
Misc.h				--Contains decln of Misc functions
Feature.h			--Contains decln of Feature Class
LabelTable.h			--Contains decln of LabelTable Class

*Source Files:
Source.cpp			--Contains the main() and the start point for the program
Pixel.cpp			--Contains class functions
Image.cpp			--Contains class functions
Histogram.cpp			--Contains class functions
Matrix.cpp			--Contains class functions
Misc.cpp			--Contains misc functions
Feature.cpp			--Contains class functions
LabelTable.cpp			--Contains class functions
Problem_1.cpp			--Contains functions for Problem 3
Problem_2.cpp			--COntains functions for Prolem 2
Problem_3.cpp			--Contains functions for Problem 1


*All files are required to compile the program

*Output will be in the form of a console window with a main menu 

*Steps to compile in Visual Studio
  Build Menu -> Build Solution		(F6)

*Steps to run in Visual Studio
  Debug Menu -> Start without debugging (CTRL + F5)


*Running the program

1) Few Functions will ask the user to input image file info again, please consider. Unable to modify completely due to deadline constrains.
2) All the images should be in the root folder of the executable

for ex

HW3
|->(All the cpp files)
|->(All the header files)
|->(All the image files)

Also the output image files will be generated in the root directorty itself.
Some functions may require user to input the image info of few output images as well, again same reason please consider.

The Problems which i was unable to solve have empty functions

The naming convention used is a modified hungarian notation i have developed for myself

eg,

Pixel pxP;
Image imOcean, imBarara[i];
int iRows, iCols;

The small case letters in each variable name point to the type of the variable, this should make it easy to read the code as i have had very little time to comments
again please consider.


The program will display a lot of information like histograms and images
some problems ask to enter the threshold from histogram, this time i have mentioned it there and then what to enter rather than for the grader to open up the histogram and
check for the threshold or anything else
However is anything is a miss please consider the immidieate previous statement in the output to see the requires action


**MATLAB FILES**
Matlab Version: R2013a
OS: Widows 8/ Windows 7
Language: C++

EE569_HW4_P1B.m			-- To Write Video of P1ab Drew
EE569_HW4_P1B_Improved.m	-- To write Video of p1c Drew
EE569_HW4_P1C.m			-- To write Video of P1c hulk
EE569_HW4_P1C_Poor.m		-- To write Video of p1ab hulk
ReadGrayRAW.m			-- Reads Gray RAW file
ReadRGBRaw.m			-- Reads RGB RAW file
