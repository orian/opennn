[x,y]=meshgrid(-1:0.1:1,-1:0.1:1);

surf(x,y,x.^2+y.^2)
xlabel('\zeta_{1}')
ylabel('\zeta_{2}')
zlabel('f(\zeta_{1},\zeta_{2})')
