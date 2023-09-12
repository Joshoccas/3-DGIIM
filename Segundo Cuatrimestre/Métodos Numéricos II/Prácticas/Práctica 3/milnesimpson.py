## módulo MS
''' Método de Milne-simpson (q=2, m=0, r=0) para resolver
el problema de valores iniciales {y}' = {F(x,{y})},
donde
 {y} = {y[0],y[1],...y[N-1]}.
X,Y
 = integrate(F,x0,y0,xfinal,N).
x0,y0 = condiciones iniciales
xfinal = valor final de x
N
 = número de subintervalos de la partición
h
 = incremento de x usado en la integración
F
 = función suplida por el usuario que devuelve el
array F(x,y) = {y'[0],y'[1],...,y'[N-1]}.
'''
def integrate(F,x0,y0,xfinal,N):
    import numpy as np
    import sympy as sp
    def MS(F,x0,y0,y1,y2,h):
        return (F(x0,y0)+4*F(x0+h,y1)+F(x0+2*h,y2))/3
    X = np.linspace(x0,xfinal,N+1)
    h = (xfinal-x0)/N
    #Definimos una variable simbolica para resolver la ecuacion
    t = sp.Symbol('t')
    y1 = y0 + h*F(x0,y0);
    Y = [y0,y1]
    for n in range(N-1):
        Y.append(sp.solve(Y[n]+h*MS(F,X[n],Y[n],Y[n+1],t,h)-t,t)[0])
    return np.array(X),np.array(Y)
