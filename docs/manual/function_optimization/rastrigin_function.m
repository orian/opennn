[x,y]=meshgrid(-5.12:0.05:5.12,-5.12:0.05:5.12);

surf(x,y, 20 + x.^2 + y.^2 - 10.*(cos(2*pi*x) + cos(2*pi*y)))
xlabel('\zeta_{1}')
ylabel('\zeta_{2}')
zlabel('f(\zeta_{1},\zeta_{2})')
