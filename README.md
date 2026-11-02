# Calculation of objective quality metrics on the GPU
The subject of this engineering thesis is the implementation of software designed to calculate objective quality metrics using a graphics processing unit (GPU) for computations.

The following metrics will be implemented: PSNR, SSIM, MS-SSIM, IV-PSNR, IV-SSIM, and IV-MS-SSIM. The software is to be written in C++, ensuring compatibility across different operating systems (specifically Windows and various Linux distributions), and will utilize the OpenCL platform.

The developed software is intended to calculate quality metrics with the necessary precision and consistency. Particular emphasis will be placed on ensuring result consistency between metrics calculated using the general-purpose processor (CPU) and the GPU.
The project will involve verifying the correctness and consistency of the results, as well as measuring performance, computational complexity, and the overhead associated with copying data to GPU memory. Additionally, the impact of using source buffers located in system memory during computation on overall performance will be measured.

# Commandline parameters

Commandline parameters are parsed from left to right.

#### General parameters

| Cmd | ParamName        | Description |
|:----|:-----------------|:------------|
|-i0  | InputFile0       | File path - input sequence 0 |
|-i1  | InputFile1       | File path - input sequence 1 |
|-nf  | NumberOfFrames   | Number of frames to be processed (optional, all=-1, default=-1) |
|-r   | ResultFile       | Output file path for printing result(s) (optional) |
|-ml  | MetricList       | List of quality metrics to be calculated, must be coma separated, quotes are required. "All" enables all available metrics. [PSNR, WSPSNR, IVPSNR, SSIM, MSSSIM, IVSSIM, IVMSSSIM] (optional, default="PSNR, WSPSNR, IVPSNR, IVSSIM") |

# Reference
* [IVPSNR] A. Dziembowski, D. Mieloch, J. Stankowski and A. Grzelka, "IV-PSNR – the objective quality metric for immersive video applications," in IEEE Transactions on Circuits and Systems for Video Technology, doi: [10.1109/TCSVT.2022.3179575](https://doi.org/10.1109/TCSVT.2022.3179575). [Available on authors webpage](http://multimedia.edu.pl/?page=publication&section=IV-PSNR---the-objective-quality-metric-for-immersive-video-applications)
* [IVSSIM] A. Dziembowski, W. Nowak, J. Stankowski, "IV-SSIM - The Structural Similarity Metric for Immersive Video", Applied Sciences, Vol. 14, No. 16, Aug 2024, doi: [10.3390/app14167090](https://doi.org/10.3390/app14167090). [Available on authors webpage](http://multimedia.edu.pl/?page=publication&section=IV-SSIM----The-Structural-Similarity-Metric-for-Immersive-Video)
* [IVSOFT1] J. Stankowski, A. Dziembowski, "IV-PSNR: Software for immersive video objective quality evaluation," SoftwareX, Volume 24, 2023, doi: [10.1016/j.softx.2023.101592](https://doi.org/10.1016/j.softx.2023.101592)
* [IVSOFT2] J. Stankowski, A. Dziembowski, "Version [7.1] – [IV-PSNR: Software for immersive video objective quality evaluation]," SoftwareX, Volume 28, 2024, doi: [10.1016/j.softx.2024.101961](https://doi.org/10.1016/j.softx.2024.101961)
* [QMIV] [GitHubRepo](https://github.com/jstankowski/QMIV)

