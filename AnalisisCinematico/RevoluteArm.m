function [H06,RPYvalues]=RevoluteArm(q0, q1, q2, q3, q4, q5, nfig) 

PI=sym('pi');
L0=7;
L1=16; % Longitud del primer eslabon
L2=14; % Longitud del tercer eslabon
L3=10;

H00   = eye(4);
H01   = DH(q0,      L0,   0,   pi/2);
H12   = DH(q1,       0,  L1,      0);
H23_a = DH(q2,       0,  L2,      0);
H23_b = DH(pi/2,     0,   0,   pi/2);
H23=H23_a*H23_b ;

H34 = DH(q3,       0,   0,  -pi/2);
H45 = DH(q4,       0,   0,   -pi/2);
H56 = DH(q5,      -L3,   0,      0);



% Cadena cinematica
H02 = H01*H12;
H03 = H02*H23;
H04 = H03*H34;
H05 = H04*H45;
H06 = H05*H56;

[Roll, Pitch, Yaw] = RPY (H06(1:3,1:3));
RPYvalues=[Roll, Pitch, Yaw];

% dibujar el robot

tf=14;
t=5;
cr='k'; ar=2;

figure(nfig);
clf
hold on

po0=Sistema3D(H00,t,'x_0','y_0','z_0',tf);
po1=Sistema3D(H01,t,'x_1','y_1','z_1',tf);
po2=Sistema3D(H02,t,'x_2','y_2','z_2',tf);
po3=Sistema3D(H03,t,'x_3','y_3','z_3',tf);
po4=Sistema3D(H04,t,'x_4','y_4','z_4',tf);
po5=Sistema3D(H05,t,'x_5','y_5','z_5',tf);
po6=Sistema3D(H06,t,'x_6','y_6','z_6',tf);

eslabon(po0,po1,cr,ar);
eslabon(po1,po2,cr,ar);
eslabon(po2,po3,cr,ar);
eslabon(po3,po4,cr,ar);
eslabon(po4,po5,cr,ar);
eslabon(po5,po6,cr,ar);
% 
% 
% 
t=5;
alto=t*0.8;
radio=t*0.2;
color='yellow';
tubo(H00*trans(0,0,-alto/2),alto,radio,color);
tubo(H01*trans(0,0,-alto/2),alto,radio,color);
tubo(H02*trans(0,0,-alto/2),alto,radio,color);
tubo(H03*trans(0,0,-alto/2),alto,radio,color);
tubo(H04*trans(0,0,-alto/2),alto,radio,color);
tubo(H05*trans(0,0,-alto/2),alto,radio,color);

giroZ(H00,[0 pi],[0.5*t 0.6*t],'',[0 1.3*t t],4);
giroZ(H01,[0 pi],[0.5*t 0.6*t],'',[0 1.3*t t],4);
giroZ(H02,[0 pi],[0.5*t 0.6*t],'',[0 1.3*t t],4);
giroZ(H03,[0 pi],[0.5*t 0.6*t],'',[0 1.3*t t],4);
giroZ(H04,[0 pi],[0.5*t 0.6*t],'',[0 1.3*t t],4);
giroZ(H05,[0 pi],[0.5*t 0.6*t],'',[0 1.3*t t],4);


axis equal
axis([-5 30 -25 25 -0.5 40]);
view([116 37])
cameratoolbar

camlight('left')
camproj('perspective')
grid on
title('Robot de Revoluta')
xlabel('X')
ylabel('Y')
zlabel('Z')

