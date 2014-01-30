[x,y]=meshgrid(-2.048:0.05:2.048,-2.048:0.05:2.048);

surf(x,y,log(1 + 100.*(y - x.^2).^2 + (1 - x).^2))
xlabel('\zeta_{1}')
ylabel('\zeta_{2}')
zlabel('log(1+f(\zeta_{1},\zeta_{2}))')
