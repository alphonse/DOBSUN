dobson <- function(L0, L, Z, P = 1013, P0 = 1013, h = 22.5, alpha = 1.4, beta = 0.01, delta = 0) {
  R = 6371.229 # mean Earth radius in km
  N <- log(L0[['UVB']]/L0[['UVA']]) - log(L[2]/L[1])   # L0 - L
  secz <- cos(Z*(pi/180))^-1
  m  <- secz-0.0018167*(secz-1)-0.002875*(secz-1)^2-0.0008083*(secz-1)^3  # eqn11, p34*
  mu <- (R + h)/sqrt((R+h)^2 - (R+0.246)^2 * sin(Z*(pi/180))^2)   # p33*
  dobson <- mean((N - beta*(m*P/P0) - (delta*secz))/(alpha*mu)*1e3)
  return(dobson)
  
  # *GAW Report: http://www.wmo.int/pages/prog/arep/gaw/documents/GAW183-Dobson-WEB.pdf
  
}


