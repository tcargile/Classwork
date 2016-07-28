%
% function S = evalspline(a,b,c,d,x,y)
%
% Inputs:
%   a-b-c-d the coefficients that define the spline
%   x are the node-points
%   y the point(s) where you want to evaluate the spline
%

function S = evalspline(a,b,c,d,x,y)

if( length(a) ~= length(x) )
  error(['The first argument (a) must be the same length as the 5th' ...
	 ' argument (x)']);
end

if( length(b) < length(x)-1 )
  error(['The second argument (b) cannot be more then one element' ...
	 ' shorter than the 5th argument (x)']);
end

if( length(c) ~= length(x) )
  error(['The third argument (c) must be the same length as the 5th' ...
	 ' argument (x)']);
end

if( length(d) < length(x)-1 )
  error(['The second argument (d) cannot be more then one element' ...
	 ' shorter than the 5th argument (x)']);
end

if( min(y) < min(x) )
  error(['The values in the 6th argument (y) should not be less than' ...
	 ' the values in the 5th argument (x)']);
end

if( max(y) > max(x) )
  error(['The values in the 6th argument (y) should not be greather' ...
	 ' than the values in the 5th argument (x)']);
end

S = zeros(size(y));

for k = 1:length(y)
  n = min([length(b) max(find(x<=y(k)))]);
  S(k) = polyval([d(n) c(n) b(n) a(n)],(y(k)-x(n)));
end
