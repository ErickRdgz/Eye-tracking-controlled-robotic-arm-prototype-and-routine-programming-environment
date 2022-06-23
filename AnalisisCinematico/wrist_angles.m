function [Q3,Q4,Q5]=wrist_angles(q0,q1,q2,phi, theta, psi)

L0=7;
L1=16;
L2=14;

H1=DH(q0,      L0,  0,   pi/2);
H2=DH(q1,      0,  L1,      0);
H3a=DH(q2,     0,  L2,      0);
H3b=DH(pi/2,   0,   0,   pi/2);
H03=H1*H2*H3a*H3b;
HR03=H03(1:3,1:3);
HR03T=transpose(HR03);

R = Rot_RPY(phi, theta, psi);

R36=HR03T*R;

Q3=atan2(R36(2,3),R36(1,3));
Q4=-atan2((sqrt(1-(R36(3,3))^2 )),(-R36(3,3)));
Q5=atan2((-R36(3,2)),(R36(3,1)));
