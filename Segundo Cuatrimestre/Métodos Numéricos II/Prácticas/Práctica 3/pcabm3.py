#módulo pcabm3
''' Método predictor-corrector Adams-Bashforth-Moulton de orden 3 para resolver el PVI
    {y}'    = F(x,{y}), donde 
    {y}     = {y[0],y[1],...,y[N-1]}
    X,Y     = integrate(F,x0,y0,xfinal,N)
    x0,y0   = condiciones iniciales
    xfinal  = valor final de x
    N       = número de subintervalos de la partición
    h       = incremento de x usado en la integración
    F       = función suplida por el usuario que devuelve el  
            array F(x,y) = {y'[0],y'[1],...,y'[N-1]}
'''

def integrate(F,x0,y0,xfinal,N):
    import numpy as np
    import eulerexplicito
    
    h = (xfinal-x0)/N
    X = np.linspace(x0,xfinal,N+1)
    Y = np.zeros(N+1)
    
    # usaremos alguno de los métodos de un paso vistos anteriormente para calcular las semillas
    # en este caso volveremos a usar Euler explicito para x_1,...,x_4
    _, Y[0:3] = eulerexplicito.integrate(F,x0,y0,x0+2*h,2)
    
    K1 = F(X[1],Y[1])
    K2 = F(X[0],Y[0])
    for i in range(2,N):
        K3 = K2
        K2 = K1
        K1 = F(X[i],Y[i])
        # predictor
        Y[i+1] = Y[i] + h*(23*K1-16*K2+5*K3)/12
        K0 = F(X[i+1],Y[i+1])
        # corrector
        Y[i+1] = Y[i] + h*(9*K0+19*K1-5*K2+K3)/24
    return np.array(X),np.array(Y)
