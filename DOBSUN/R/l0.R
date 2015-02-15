l0 <- function(uva, uvb, Z, graph = T) {
  airmass <- log(cos(Z*(pi/180))^-1)
  uva <- log(uva)
  uvb <- log(uvb)
  uva.fit <- lm(uva ~ airmass)
  uvb.fit <- lm(uvb ~ airmass)
  L0 <- c(UVA = exp(as.numeric(coef(uva.fit)[1])),
          UVB = exp(as.numeric(coef(uvb.fit)[1]))
  )
  
  # plot data if desired -----
  if (graph == T) {
    magplot(airmass, uva, 
            ylim = c(min(c(uva, uvb)), max(log(L0))), 
            xlim = c(0, max(airmass)+0.25),
            pch = 16, col = 'purple',
            xaxs = 'i',
            yaxs = 'i',
            xlab = 'log[Airmass] (relative)',
            ylab = 'Luminosity (V)',
            main = paste('Langley Plot for ', Sys.Date())
            )
    points(airmass, uvb, pch = 15, col = 'violet')
    abline(uva.fit, col = 'purple', lty = 'dashed')
    abline(uvb.fit, col = 'violet', lty = 'dotted')
    legend('topright',
           legend = c(paste('UVA (L0 = ', round(log(L0[1]), digits = 2), 'V)'),
                      paste('UVB (L0 = ', round(log(L0[2]), digits = 2), 'V)')),
           bty = 'n',
           cex = 0.75,
           pch = c(16, 15),
           col = c('purple', 'violet')
      )
  }
  uva.fit
  uvb.fit
  return(list(L0 = L0, fits = list(UVA = uva.fit, UVB = uvb.fit)))
}