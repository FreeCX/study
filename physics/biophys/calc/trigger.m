% using
% t0 = [0, 50]
% x0 = [5, 1]
% L0 = [3, 5]
% [t,x] = ode45( @trigger, t0, x0, [], L0)

function dx = trigger(t,x,L)
    dx = [L(1)/(1+x(2)^2) - x(1); L(2)/(1+x(1)^2) - x(2)];
end