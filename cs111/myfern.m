function myfern(n)
% MYFERN : plot a fractal fern
%
% myfern(n) plots n points.  Default is n = 1000

if nargin < 1
    n = 10000;
end;

p  = [ .85  .92  .99  1.00];
A = [.5,0; 0, .5]
b1 = [0; 0];
b2 = [.5; 0];
b3 = [.25; 0.433];


x  = [0 ; 0];        % start x at the base of the stem

figure; 
plot(x(1),x(2),'g.');

hold on;
for i = 1:n
   r = rand;
   if r < p(1)
      x = A*x + b1;    % 85% of the time: move x up toward the tip
   elseif r < p(2)
      x = A*x + b2;    %  7% of the time: move x into the lower right frond
   elseif r < p(3)
      x = A*x + b3;    %  7% of the time: move x into the lower left frond

   end
   plot(x(1),x(2),'g.','markersize',5);
   drawnow
end