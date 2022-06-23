clear all
%-----------------------------------------------------------------
% Parametros de inicio 
Xf=14;
Yf= 0;
Zf=13;
roll=0;    %x
pitch=0;  %y
yaw=0;     %z
%-----------------------------------------------------------------


[phi,theta,psi]=RPYadjusment(roll,pitch,yaw);             % convert Euler Angles to Rad
[Xw,Yw,Zw]=wrist_center(Xf,Yf,Zf,phi,theta,psi);          % find wrist center 
[Q0,Q1,Q2]=geometric_IK(Xw,Yw,Zw);                        % find first three joints with geometric method 
[Q3,Q4,Q5]=wrist_angles(Q0,Q1,Q2,phi, theta, psi);        % find the last three joints with wrist kinematic decoupling definition
[H06,RPYvalues]=RevoluteArm(Q0, Q1, Q2, Q3, Q4, Q5, 1);   % graphic simolation

%rad to deg
Q0=Q0*(180/pi);
Q1=Q1*(180/pi);
Q2=Q2*(180/pi);
Q3=Q3*(180/pi);
Q4=Q4*(180/pi);
Q5=Q5*(180/pi);

[A0,A1,A2,A3,A4,A5]=Arm_angles(Q0,Q1,Q2,Q3,Q4,Q5);        % ModelAngles to ArmAngles 

% print results 
ModelAngles=[Q0 Q1 Q2 Q3 Q4 Q5]
ArmAngles=[A0 A1 A2 A3 A4 A5]
RPYvalues=RPYvalues*(180/pi)









