function [Q0,Q1,Q2]=geometric_IK(Xw,Yw,Zw)
L0=7;
L1=16;
L2=14;

H_xy=sqrt(Yw^2+Xw^2);

Q0=atan2(Yw,Xw);

C2=(  (H_xy^2) + (Zw-L0)^2 - L1^2 - L2^2   )/(2*L1*L2);
Q2=atan2(sqrt(1-C2^2),C2);

Q1=  pi/2- (atan2(H_xy,(Zw-L0))-atan2( (L2*sin(Q2)),(L1+L2*cos(Q2)) ));

Q2=-Q2;