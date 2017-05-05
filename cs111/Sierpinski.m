function Sierpinski
%FERN  MATLAB implementation of the Fractal Fern.
%   Michael Barnsley, Fractals Everywhere, Academic Press, 1993.
%   This version runs forever, or until stop is toggled.
%   See also FINITEFERN.

%   Copyright 2013 Cleve Moler
%   Copyright 2013 The MathWorks, Inc.

shg
clf reset
set(gcf,'color','white','menubar','none', ...
   'numbertitle','off','name','Fractal Fern')
x = [.5; .5];
h = plot(x(1),x(2),'.');
darkgreen = [0 2/3 0];
set(h,'markersize',1,'color',darkgreen,'erasemode','none');
axis([-3 3 0 10])
axis off
stop = uicontrol('style','toggle','string','stop', ...
   'background','white');
drawnow

p  = [ .85  .92  .99  1.00];
A  = [ .5  0; 0  .5];
b1 = [0; 0];
b2 = [0.5; 0];
b3 = [0.25; .433];

cnt = 1;
tic
while ~get(stop,'value')
   r = rand;
   if r < p(1)
      x = A*x + b1;
   elseif r < p(2)
      x = A*x + b2;
   elseif r < p(3)
      x = A*x + b3;
   end
   set(h,'xdata',x(1),'ydata',x(2));
   drawnow
   cnt = cnt + 1;
end
t = toc;
s = sprintf('%8.0f points in %6.3f seconds',cnt,t);
text(-1.5,-0.5,s,'fontweight','bold');
set(stop,'style','pushbutton','string','close','callback','close(gcf)')
