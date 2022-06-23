function [phi,theta,psi]=RPYadjusment(roll,pitch,yaw)
phi=   roll*pi/180;   %Z
theta= pitch*pi/180;  %y
psi =   yaw*pi/180;   %x