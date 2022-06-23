function [Xw, Yw, Zw]=wrist_center(Xf,Yf,Zf,phi,theta,psi)
L3=10;
R = Rot_RPY(phi, theta, psi);
Xw= Xf+L3*R(1,3);
Yw= Yf+L3*R(2,3);
Zw= Zf+L3*R(3,3);
end
