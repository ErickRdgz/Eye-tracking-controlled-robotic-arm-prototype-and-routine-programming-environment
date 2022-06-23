clear all
%-----------------------------------------------------------------
% Parametros de inicio 
Q0=0;
Q1=90;
Q2=-90;
Q3=0;
Q4=-90;
Q5=0;
%-----------------------------------------------------------------

[A0,A1,A2,A3,A4,A5]=Arm_angles(Q0,Q1,Q2,Q3,Q4,Q5);        % ModelAngles to ArmAngles 
ArmAngles=[A0 A1 A2 A3 A4 A5]                             % Print arm angles

%deg to rad
Q0=Q0*(pi/180);
Q1=Q1*(pi/180);
Q2=Q2*(pi/180);
Q3=Q3*(pi/180);
Q4=Q4*(pi/180);
Q5=Q5*(pi/180);

[H06,RPYvalues]=RevoluteArm(Q0, Q1, Q2, Q3, Q4, Q5, 1)   % graphic simulation
 RPYvalues=RPYvalues*(180/pi)                            % Euler angles





