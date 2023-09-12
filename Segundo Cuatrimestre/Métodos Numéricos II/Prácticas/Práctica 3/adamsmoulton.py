## módulo AM
''' Método de Adams-Moulton q=1, m=0, r=0 (con k = 1) para resolver
el problema de valores iniciales 
{y}'    = {F(x,{y})}, donde
{y}     = {y[0],y[1],...y[N-1]}.
X,Y     = integrate(F,x0,y0,xfinal,N).
x0,y0   = condiciones iniciales
xfinal  = valor final de x
N       = número de subintervalos de la partición
h       = incremento de x usado en la integración
F       = función suplida por el usuario que devuelve el
        array F(x,y) = {y'[0],y'[1],...,y'[N-1]}.
'''
def integrate(F,x0,y0,xfinal,N):
    import numpy as np
    import sympy as sp
    def AM(F,x0,y0,t,h):
        return 1/2*(F(x0,y0)+F(x0+h,t))
    X = np.linspace(x0,xfinal,N+1)
    h = (xfinal-x0)/N
#Definimos una variable simbolica para resolver la ecuacion
    t = sp.Symbol('t')
    Y = [y0]
    for n in range(N):
        Y.append(sp.solve(Y[n]+h*AM(F,X[n],Y[n],t,h)-t,t)[0])
    return np.array(X),np.array(Y)
