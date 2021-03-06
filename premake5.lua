workspace "GraphicAlgorithm"
   configurations { "Debug", "Release" }
   platforms {"x64"}   
   
include "Frame"   
include "BRDF_Sampler"   
include "DepthToPositionAndNormal"   
include "FitLTCMatrix"   
include "SH_Sampler"   
include "001_Reflective shadow map"   
include "002_Non-interleaved Deferred Shading of Interleaved Sample"   
include "003_Stochastic Light Culling"   
include "004_Metalights Improved Interleaved Shading"   
include "005_Interactive Order Independent Transparency"   
include "006_Wang Tiles for Image and Texture Generation"   
include "007_Tile Shading"   
include "008_A Non-Photorealistic Lighting Model"   
include "009_Spherical Harmonic Lighting The Gritty Details"   
include "010_RealTimePolygonalLightShadingWithLinearlyTransformedCosines"   
include "011_An Efficient Representation for Irradiance Environment Maps"   
include "012_Real Time Concurrent Linked List Construction on the GPU"   
include "013_Fourier Opacity Optimization for Scalable Exploration"   
include "014_Approximating Dynamic Global Illumination in Image Space"   
include "015_Image Space Horizon Based Ambient Occlusion"   
include "016_Cascaded Light Propagation Volumes for Real-Time Indirect Illumination"   
include "017_Forward Light Cuts A Scalable Approach to RealTime Global Illumination"   
include "018_Cascaded Shadow Maps"   
include "019_A Survey of Efficient Representations  for Independent Unit Vectors"   
include "020_Real-time Approximation to Large Convolution Kernel"   
include "021_Real-time indirect illumination by virtual planar area lights"   
include "022_Variance Shadow Maps"   
include "023_Efficient GPU Screen-Space Ray Tracing"   
include "024_Real-Time Global Illumination using Precomputed Light Field Probes"   
include "025_Exponential Shadow Maps"   
include "026_Moment Shadow Mapping"   
include "027_FidelityFX Super Resolution"   
include "028_Mobile Friendly FSR"   
