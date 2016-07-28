%%%
%%% This is a template for Math 541 - HW#5
%%%
%%% It gives you the structure of the program, but *you* have
%%% to fill in the missing details!!!
%%%

clear
format long
load duckdata
f = f';                       % reset f as a column vector
x = x';                       % reset x as a column vector
n = length(x);                % set n equal to the number of x-values
a = f;                        % set a equal to the column vector 'f'
h = diff(x);

% Matrix 'T' is the compact form of an nxn matrix 'A' where T(:,1) is
% the sub-diag of A, T(:,2) is the diag of A, and T(:,3) is the
% super-diag of A
%
% Here "A" is the matrix corresponding the the linear system for
% getting the c-coefficients for a natural spline
%
% 'rhs' is the right-hand-side...

%%%(YOUR CODE HERE)

% First compute Tsub:
for i=2:n-1
    T(i,1) = h(i-1,1);
end

T(n,1) = 0;
T(1,3) = 0;

% Second compute Tsuper:
for i=2:n-1
    T(i,3) = h(i,1);
end

T(1,2) = 1;
T(n,2) = 1;

for i=2:n-1
    T(i,2) = 2 * (h(i-1,1) + h(i,1));
end

% Compute rhs:

rhs(1,1) = 0;
%rhs(1,1) = 3 * (a(2) - a(1))/h(1);

for i=3:n
    rhs(i-1,1) = 3 * (a(i) - a(i-1))/h(i-1) - 3 * (a(i-1) - a(i-2))/h(i-2);
end

rhs(n,1) = 0;
%rhs(n,1) = 0 - 3 * (a(n) - a(n-1))/h(n-1);

%%%(END YOUR CODE, PART 1)

c = trisolve(T,rhs);          % function that solves for c where T*c=rhs

%
% Next, build vectors 'b' and 'd'
%

%%%(YOUR CODE HERE)

% Compute b:
for i=1:n-1
    b(i,1) = (a(i+1) - a(i))/h(i) - h(i)*(2*c(i) + c(i+1))/3;
end

% Compute d:
for i=1:n-1
    d(i,1) = (c(i+1) - c(i))/(3*h(i));
end

%%%(END YOUR CODE, PART 2)

y = min(x):0.01:max(x);       % set y to arbitary pts to evaluate
                              % the spline at 
y = y';                       % reset y as a column vector 

S = evalspline(a,b,c,d,x,y);  % function that uses the coeff
                              % defining the spline to evaluate the
                              % spline at each pt in 'y' 

% graph pts (x,f) and the spline that fits these pts

plot(y,S,'b-',x,f,'mo','markersize',7)
grid on
disp('This should look like the duck in the book...')
disp('...except maybe for some scaling of the axes.')
disp(' ')

%%% Make sure these are column vectors...
a = reshape(a,length(a),1);
b = reshape(b,length(b),1);
c = reshape(c,length(c),1);
d = reshape(d,length(d),1);

disp('Coefficients [a b c d]')
disp([a [b;0] c [d;0]])


%%%(NOTE) In order to answer all questions, you may have to dig
%%%(NOTE) through the code/results carefully to get all the
%%%(NOTE) information you need.
