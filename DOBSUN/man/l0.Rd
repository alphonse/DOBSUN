\name{l0}
\alias{l0}
\title{
Calculate the top of the atmosphere luminosity
}
\description{
Calculates the top of the atmosphere luminosity for UVA and UVB light given surface measurements of each at varying relative airmass thicknesses.
}
\usage{
l0(uva, uvb, Z, graph = T)
}
\arguments{
  \item{uva}{A numeric vector of uva intensity values in the same units as \code{uvb}}
  \item{uvb}{A numeric vector of uvb intensity values in the same units as \code{uva}}
  \item{Z}{A numeric vector of solar zenith angles in degrees}
  \item{graph}{A \code{TRUE} or \code{FALSE} value specifying whether to output a Langley plot of the data.}
}

\value{
A list containing (1) a named numeric vector of L0 for UVA and UVB sensors and (2) a list containing two functions representing the linear models used to calculate UVA and UVB L0 values.

Optionally, a Langley plot of the data can be printed to the grpahics device.
}
\references{
\link{http://www.wmo.int/pages/prog/arep/gaw/documents/GAW183-Dobson-WEB.pdf}
}

\author{
Al Fischer
}

\seealso{
{\code{dobson}}
}

\examples{
uva <- c(200, 250, 300)

uvb <- c(500, 575, 650)

Z <- c(60, 58, 55)

# calculate L0

L0 <- l0(uva, uvb, Z)
}
% Add one or more standard keywords, see file 'KEYWORDS' in the
% R documentation directory.
\keyword{ ozone }
\keyword{ Dobson }
\keyword{ Langley }
