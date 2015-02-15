\name{dobson}
\alias{dobson}
\title{
Calculate column ozone thickness in Dobson units.
}
\description{
Calculate the atmospheric column ozone thickness given measurements of UVA and UVB radiation at Earth's surface.}
\usage{
dobson(L0, L, Z, P = 1013, P0 = 1013, h = 22.5, alpha = 1.4, beta = 0.01, delta = 0)
}
%- maybe also 'usage' for other objects documented here.
\arguments{
  \item{L0}{Top of the atmosphere (TOA) luminosity in the same units as \code{L}; can be calculated with \code{l0}.}
  \item{L}{Surface luminosity in the same units as \code{L0}}
  \item{Z}{Solar zenith angle at the time of measurement (degrees)}
  \item{P}{Measurement station pressure (mbar)}
  \item{P0}{Mean sea level pressure (mbar)}
  \item{h}{Height of ozone layer above sea level (km)}
  \item{alpha}{The difference in ozone absorption coefficient at UVA and UVB}
  \item{beta}{The difference in the Rayleigh coefficients for air at UVA and UVB}
  \item{delta}{The difference in the scattering coefficients for aerosols}
}

\value{
A numeric representing the column ozone thickness in Dobson units.
}
\references{
  http://www.wmo.int/pages/prog/arep/gaw/documents/GAW183-Dobson-WEB.pdf
}
\author{
Al Fischer
}


%% ~Make other sections like Warning with \section{Warning }{....} ~

\seealso{
\code{\link{DOBSUN:l0}}
\examples{
# make up some data

uva <- c(200, 250, 300)

uvb <- c(500, 575, 650)

Z   <- c(60, 58, 55)

# calculate L0

L0 <- l0(uva, uvb, Z)

# calculate DU

dobson(L0, c(uva[2], uvb[2], Z))
}

% Add one or more standard keywords, see file 'KEYWORDS' in the
% R documentation directory.
\keyword{ ozone }
\keyword{ Dobson }
