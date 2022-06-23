function [A0,A1,A2,A3,A4,A5]=Arm_angles(Q0,Q1,Q2,Q3,Q4,Q5)
A0=Q0+90; 
A1=170-Q1;
A2=Q1+Q2+105;
A3=Q3+86;
A4=35-Q4;
A5=Q5+90;

