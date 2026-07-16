// Auto-generated Optimized XGBoost Micro-Model C code for ESP32
// Input features: N, P, K, temperature, humidity, pH

#include <math.h>
#include <stdint.h>

#ifndef NAN
    #define NAN (0.0f/0.0f)
#endif
float score(float * input) {
    float var0;
    if (input[4] < 86.9719) {
        if (input[0] < 81.0) {
            if (input[2] < 30.744875) {
                if (input[4] < 71.393486) {
                    if (input[4] < 58.5967) {
                        var0 = -11068.462;
                    } else {
                        var0 = -17263.61;
                    }
                } else {
                    if (input[1] < 31.77194) {
                        var0 = 14673.438;
                    } else {
                        var0 = -4265.9116;
                    }
                }
            } else {
                if (input[4] < 85.09812) {
                    if (input[5] < 5.769785) {
                        var0 = 953.0335;
                    } else {
                        var0 = -6863.564;
                    }
                } else {
                    if (input[0] < 43.347652) {
                        var0 = 30694.402;
                    } else {
                        var0 = -4484.0024;
                    }
                }
            }
        } else {
            if (input[2] < 242.0) {
                if (input[1] < 71.0) {
                    if (input[0] < 110.15318) {
                        var0 = -5568.337;
                    } else {
                        var0 = 6267.814;
                    }
                } else {
                    if (input[4] < 72.646) {
                        var0 = 9082.355;
                    } else {
                        var0 = 45129.516;
                    }
                }
            } else {
                if (input[4] < 69.991) {
                    if (input[5] < 5.663428) {
                        var0 = -3885.8772;
                    } else {
                        var0 = -17790.893;
                    }
                } else {
                    var0 = 26655.197;
                }
            }
        }
    } else {
        if (input[0] < 73.0) {
            if (input[2] < 116.0) {
                if (input[4] < 89.236465) {
                    if (input[1] < 33.596798) {
                        var0 = 40203.562;
                    } else {
                        var0 = 11439.572;
                    }
                } else {
                    if (input[1] < 77.32301) {
                        var0 = 46898.12;
                    } else {
                        var0 = 6261.9624;
                    }
                }
            } else {
                if (input[0] < 50.0) {
                    if (input[5] < 6.902751) {
                        var0 = 10206.767;
                    } else {
                        var0 = -11998.648;
                    }
                } else {
                    if (input[4] < 91.49883) {
                        var0 = -8833.781;
                    } else {
                        var0 = 3281.3853;
                    }
                }
            }
        } else {
            if (input[1] < 56.432) {
                if (input[2] < 1.0) {
                    if (input[0] < 82.0) {
                        var0 = 32722.86;
                    } else {
                        var0 = -8790.374;
                    }
                } else {
                    if (input[3] < 33.04688) {
                        var0 = -12121.107;
                    } else {
                        var0 = 4198.6943;
                    }
                }
            } else {
                if (input[3] < 23.894861) {
                    if (input[5] < 6.6590166) {
                        var0 = -13916.416;
                    } else {
                        var0 = -72.60156;
                    }
                } else {
                    if (input[2] < 88.0) {
                        var0 = 40365.867;
                    } else {
                        var0 = -4043.4592;
                    }
                }
            }
        }
    }
    float var1;
    if (input[4] < 86.9719) {
        if (input[0] < 81.0) {
            if (input[2] < 30.744875) {
                if (input[4] < 83.83626) {
                    if (input[2] < 10.0) {
                        var1 = -8348.04;
                    } else {
                        var1 = -14441.271;
                    }
                } else {
                    if (input[1] < 31.77194) {
                        var1 = 30981.348;
                    } else {
                        var1 = -753.41156;
                    }
                }
            } else {
                if (input[4] < 85.09812) {
                    if (input[4] < 36.52781) {
                        var1 = -20419.969;
                    } else {
                        var1 = -4020.3042;
                    }
                } else {
                    if (input[0] < 42.754875) {
                        var1 = 26764.166;
                    } else {
                        var1 = -2903.7017;
                    }
                }
            }
        } else {
            if (input[2] < 242.0) {
                if (input[1] < 71.0) {
                    if (input[0] < 109.686874) {
                        var1 = -4999.575;
                    } else {
                        var1 = 5126.5415;
                    }
                } else {
                    if (input[4] < 73.89817) {
                        var1 = 7867.9175;
                    } else {
                        var1 = 38788.324;
                    }
                }
            } else {
                if (input[4] < 69.991) {
                    if (input[5] < 5.663428) {
                        var1 = -3330.7522;
                    } else {
                        var1 = -15134.499;
                    }
                } else {
                    var1 = 24656.059;
                }
            }
        }
    } else {
        if (input[0] < 73.0) {
            if (input[2] < 116.0) {
                if (input[4] < 90.10853) {
                    if (input[1] < 33.596798) {
                        var1 = 34344.574;
                    } else {
                        var1 = 14540.541;
                    }
                } else {
                    if (input[0] < 57.0) {
                        var1 = 41722.242;
                    } else {
                        var1 = 29387.043;
                    }
                }
            } else {
                if (input[2] < 167.9841) {
                    if (input[1] < 61.141) {
                        var1 = -8892.275;
                    } else {
                        var1 = 4233.307;
                    }
                } else {
                    if (input[3] < 27.141937) {
                        var1 = 8504.372;
                    } else {
                        var1 = 23182.94;
                    }
                }
            }
        } else {
            if (input[1] < 56.432) {
                if (input[2] < 1.0) {
                    if (input[0] < 82.0) {
                        var1 = 29450.572;
                    } else {
                        var1 = -7735.5283;
                    }
                } else {
                    if (input[3] < 33.04688) {
                        var1 = -10308.846;
                    } else {
                        var1 = 3647.6165;
                    }
                }
            } else {
                if (input[3] < 23.894861) {
                    if (input[5] < 6.6590166) {
                        var1 = -12246.444;
                    } else {
                        var1 = -65.34219;
                    }
                } else {
                    if (input[2] < 88.0) {
                        var1 = 34506.305;
                    } else {
                        var1 = -3558.2454;
                    }
                }
            }
        }
    }
    float var2;
    if (input[4] < 86.9719) {
        if (input[0] < 87.76143) {
            if (input[2] < 30.744875) {
                if (input[4] < 69.606) {
                    if (input[4] < 59.001213) {
                        var2 = -7771.692;
                    } else {
                        var2 = -12842.56;
                    }
                } else {
                    if (input[4] < 83.83626) {
                        var2 = -2390.6235;
                    } else {
                        var2 = 11591.447;
                    }
                }
            } else {
                if (input[5] < 5.769785) {
                    if (input[4] < 41.51) {
                        var2 = -19437.262;
                    } else {
                        var2 = 3600.562;
                    }
                } else {
                    if (input[4] < 82.14809) {
                        var2 = -5591.7725;
                    } else {
                        var2 = 6525.014;
                    }
                }
            }
        } else {
            if (input[2] < 222.8815) {
                if (input[3] < 26.286404) {
                    if (input[1] < 68.776) {
                        var2 = -4849.027;
                    } else {
                        var2 = 4715.872;
                    }
                } else {
                    if (input[1] < 71.0) {
                        var2 = 5317.284;
                    } else {
                        var2 = 19435.13;
                    }
                }
            } else {
                if (input[1] < 46.697334) {
                    if (input[3] < 28.297476) {
                        var2 = 15024.143;
                    } else {
                        var2 = -3124.6865;
                    }
                } else {
                    if (input[4] < 69.991) {
                        var2 = -12289.968;
                    } else {
                        var2 = 22806.854;
                    }
                }
            }
        }
    } else {
        if (input[0] < 73.0) {
            if (input[2] < 110.0) {
                if (input[4] < 90.10853) {
                    if (input[0] < 67.0) {
                        var2 = 24231.791;
                    } else {
                        var2 = -17347.73;
                    }
                } else {
                    if (input[1] < 77.32301) {
                        var2 = 34565.28;
                    } else {
                        var2 = -2759.9077;
                    }
                }
            } else {
                if (input[0] < 50.0) {
                    if (input[3] < 26.286404) {
                        var2 = 7023.4766;
                    } else {
                        var2 = 17306.6;
                    }
                } else {
                    if (input[4] < 91.49883) {
                        var2 = -7268.9546;
                    } else {
                        var2 = 2123.357;
                    }
                }
            }
        } else {
            if (input[1] < 56.432) {
                if (input[2] < 1.0) {
                    if (input[0] < 82.0) {
                        var2 = 26505.518;
                    } else {
                        var2 = -6807.2646;
                    }
                } else {
                    if (input[3] < 33.04688) {
                        var2 = -8767.539;
                    } else {
                        var2 = 3168.8674;
                    }
                }
            } else {
                if (input[3] < 23.894861) {
                    if (input[5] < 6.6590166) {
                        var2 = -10776.872;
                    } else {
                        var2 = -58.807816;
                    }
                } else {
                    if (input[2] < 88.0) {
                        var2 = 29497.322;
                    } else {
                        var2 = -3131.2554;
                    }
                }
            }
        }
    }
    float var3;
    if (input[4] < 75.03859) {
        if (input[0] < 100.60943) {
            if (input[2] < 30.744875) {
                if (input[4] < 36.52781) {
                    var3 = -17984.594;
                } else {
                    if (input[4] < 55.17911) {
                        var3 = -1037.3818;
                    } else {
                        var3 = -9951.633;
                    }
                }
            } else {
                if (input[5] < 5.769785) {
                    if (input[4] < 41.51) {
                        var3 = -16643.154;
                    } else {
                        var3 = 2906.3696;
                    }
                } else {
                    if (input[3] < 26.226095) {
                        var3 = -7116.234;
                    } else {
                        var3 = -2909.0872;
                    }
                }
            }
        } else {
            if (input[1] < 27.746605) {
                if (input[2] < 38.65655) {
                    if (input[0] < 133.58269) {
                        var3 = 7241.67;
                    } else {
                        var3 = -5582.9727;
                    }
                } else {
                    if (input[5] < 5.5149274) {
                        var3 = -2120.1636;
                    } else {
                        var3 = 20947.68;
                    }
                }
            } else {
                if (input[2] < 242.0) {
                    if (input[2] < 120.0) {
                        var3 = -2919.332;
                    } else {
                        var3 = 12175.872;
                    }
                } else {
                    if (input[5] < 5.663428) {
                        var3 = -2118.2415;
                    } else {
                        var3 = -11250.598;
                    }
                }
            }
        }
    } else {
        if (input[0] < 58.46179) {
            if (input[2] < 89.88595) {
                if (input[4] < 83.83626) {
                    if (input[2] < 50.196278) {
                        var3 = -1469.0857;
                    } else {
                        var3 = 25551.197;
                    }
                } else {
                    if (input[1] < 34.0) {
                        var3 = 31334.51;
                    } else {
                        var3 = 19126.049;
                    }
                }
            } else {
                if (input[4] < 85.965385) {
                    if (input[5] < 6.8539267) {
                        var3 = -9696.789;
                    } else {
                        var3 = 5206.7075;
                    }
                } else {
                    if (input[1] < 54.74942) {
                        var3 = 19363.717;
                    } else {
                        var3 = 5952.8125;
                    }
                }
            }
        } else {
            if (input[1] < 60.40199) {
                if (input[3] < 32.860783) {
                    if (input[2] < 10.0) {
                        var3 = 2283.9382;
                    } else {
                        var3 = -7704.696;
                    }
                } else {
                    if (input[2] < 77.703125) {
                        var3 = 26778.602;
                    } else {
                        var3 = -8919.403;
                    }
                }
            } else {
                if (input[3] < 24.532112) {
                    if (input[1] < 76.129616) {
                        var3 = 416.19473;
                    } else {
                        var3 = 21951.99;
                    }
                } else {
                    if (input[2] < 100.0) {
                        var3 = 32746.379;
                    } else {
                        var3 = 2914.193;
                    }
                }
            }
        }
    }
    float var4;
    if (input[4] < 75.03859) {
        if (input[0] < 92.0) {
            if (input[4] < 36.52781) {
                var4 = -15137.861;
            } else {
                if (input[5] < 5.6757455) {
                    if (input[3] < 31.652) {
                        var4 = -950.2225;
                    } else {
                        var4 = 15026.682;
                    }
                } else {
                    if (input[1] < 56.432) {
                        var4 = -7410.1724;
                    } else {
                        var4 = -821.48267;
                    }
                }
            }
        } else {
            if (input[1] < 27.746605) {
                if (input[2] < 38.65655) {
                    if (input[0] < 133.58269) {
                        var4 = 4331.7036;
                    } else {
                        var4 = -4767.001;
                    }
                } else {
                    if (input[5] < 5.5149274) {
                        var4 = -2005.3347;
                    } else {
                        var4 = 17317.951;
                    }
                }
            } else {
                if (input[2] < 222.8815) {
                    if (input[2] < 136.0) {
                        var4 = -2253.7996;
                    } else {
                        var4 = 13241.275;
                    }
                } else {
                    if (input[1] < 46.697334) {
                        var4 = 2293.85;
                    } else {
                        var4 = -9312.341;
                    }
                }
            }
        }
    } else {
        if (input[0] < 58.46179) {
            if (input[2] < 89.88595) {
                if (input[4] < 89.236465) {
                    if (input[1] < 33.596798) {
                        var4 = 21398.531;
                    } else {
                        var4 = 1946.0125;
                    }
                } else {
                    if (input[1] < 77.32301) {
                        var4 = 25644.033;
                    } else {
                        var4 = 1143.5552;
                    }
                }
            } else {
                if (input[4] < 83.83626) {
                    if (input[5] < 6.8539267) {
                        var4 = -8935.971;
                    } else {
                        var4 = 4620.953;
                    }
                } else {
                    if (input[2] < 118.98438) {
                        var4 = 13517.305;
                    } else {
                        var4 = 4978.504;
                    }
                }
            }
        } else {
            if (input[1] < 60.40199) {
                if (input[3] < 32.860783) {
                    if (input[3] < 22.979664) {
                        var4 = 1438.6549;
                    } else {
                        var4 = -6731.5044;
                    }
                } else {
                    if (input[2] < 77.703125) {
                        var4 = 22905.266;
                    } else {
                        var4 = -7715.2837;
                    }
                }
            } else {
                if (input[3] < 24.532112) {
                    if (input[1] < 64.764984) {
                        var4 = -6750.6807;
                    } else {
                        var4 = 11950.182;
                    }
                } else {
                    if (input[5] < 7.1903377) {
                        var4 = 27966.545;
                    } else {
                        var4 = 296.89017;
                    }
                }
            }
        }
    }
    float var5;
    if (input[4] < 75.03859) {
        if (input[0] < 100.60943) {
            if (input[2] < 45.0) {
                if (input[4] < 55.887) {
                    if (input[1] < 40.82344) {
                        var5 = 9897.516;
                    } else {
                        var5 = -8431.093;
                    }
                } else {
                    if (input[1] < 47.556) {
                        var5 = -9025.292;
                    } else {
                        var5 = -3973.0757;
                    }
                }
            } else {
                if (input[3] < 26.169859) {
                    if (input[4] < 48.625385) {
                        var5 = -9560.231;
                    } else {
                        var5 = -2994.4246;
                    }
                } else {
                    if (input[1] < 86.0) {
                        var5 = -457.37207;
                    } else {
                        var5 = 26781.135;
                    }
                }
            }
        } else {
            if (input[1] < 27.746605) {
                if (input[2] < 38.65655) {
                    if (input[0] < 133.58269) {
                        var5 = 5542.5996;
                    } else {
                        var5 = -4070.2854;
                    }
                } else {
                    if (input[2] < 112.69621) {
                        var5 = 17098.072;
                    } else {
                        var5 = 6991.25;
                    }
                }
            } else {
                if (input[2] < 222.8815) {
                    if (input[2] < 120.0) {
                        var5 = -2144.0876;
                    } else {
                        var5 = 10188.416;
                    }
                } else {
                    if (input[1] < 46.697334) {
                        var5 = 1974.3506;
                    } else {
                        var5 = -7866.1924;
                    }
                }
            }
        }
    } else {
        if (input[0] < 57.0) {
            if (input[1] < 35.0) {
                if (input[4] < 81.52184) {
                    if (input[5] < 6.9777) {
                        var5 = -4522.422;
                    } else {
                        var5 = 28859.303;
                    }
                } else {
                    if (input[2] < 106.0) {
                        var5 = 22986.936;
                    } else {
                        var5 = -5694.037;
                    }
                }
            } else {
                if (input[3] < 30.0) {
                    if (input[4] < 89.68367) {
                        var5 = -4783.358;
                    } else {
                        var5 = 7388.265;
                    }
                } else {
                    if (input[1] < 76.129616) {
                        var5 = 21185.852;
                    } else {
                        var5 = -7579.4014;
                    }
                }
            }
        } else {
            if (input[1] < 60.40199) {
                if (input[3] < 33.04688) {
                    if (input[2] < 10.0) {
                        var5 = 2474.8613;
                    } else {
                        var5 = -5631.544;
                    }
                } else {
                    if (input[5] < 6.7) {
                        var5 = 1752.4066;
                    } else {
                        var5 = 25345.549;
                    }
                }
            } else {
                if (input[3] < 24.532112) {
                    if (input[1] < 76.129616) {
                        var5 = -153.54926;
                    } else {
                        var5 = 16141.399;
                    }
                } else {
                    if (input[5] < 7.1903377) {
                        var5 = 23512.236;
                    } else {
                        var5 = 255.32672;
                    }
                }
            }
        }
    }
    float var6;
    if (input[4] < 75.03859) {
        if (input[0] < 92.0) {
            if (input[2] < 26.0) {
                if (input[2] < 11.0) {
                    if (input[1] < 70.0) {
                        var6 = -4115.62;
                    } else {
                        var6 = 6693.3506;
                    }
                } else {
                    if (input[0] < 60.512794) {
                        var6 = -8861.902;
                    } else {
                        var6 = -4173.7383;
                    }
                }
            } else {
                if (input[5] < 5.076736) {
                    if (input[2] < 38.65655) {
                        var6 = 33521.99;
                    } else {
                        var6 = 2090.9707;
                    }
                } else {
                    if (input[5] < 6.866002) {
                        var6 = -1669.0398;
                    } else {
                        var6 = -5614.549;
                    }
                }
            }
        } else {
            if (input[1] < 27.746605) {
                if (input[2] < 38.65655) {
                    if (input[4] < 55.450592) {
                        var6 = -6415.053;
                    } else {
                        var6 = 3183.4238;
                    }
                } else {
                    if (input[3] < 23.970814) {
                        var6 = -10627.746;
                    } else {
                        var6 = 12567.817;
                    }
                }
            } else {
                if (input[2] < 91.0) {
                    if (input[4] < 64.19913) {
                        var6 = -3692.1997;
                    } else {
                        var6 = 3434.7607;
                    }
                } else {
                    if (input[2] < 222.8815) {
                        var6 = 6210.4526;
                    } else {
                        var6 = -6323.7983;
                    }
                }
            }
        }
    } else {
        if (input[0] < 57.0) {
            if (input[2] < 89.88595) {
                if (input[4] < 90.10853) {
                    if (input[1] < 33.596798) {
                        var6 = 15672.753;
                    } else {
                        var6 = 1890.8905;
                    }
                } else {
                    if (input[3] < 24.971786) {
                        var6 = 15549.903;
                    } else {
                        var6 = 20980.926;
                    }
                }
            } else {
                if (input[4] < 85.965385) {
                    if (input[5] < 6.8539267) {
                        var6 = -6485.3477;
                    } else {
                        var6 = 4673.374;
                    }
                } else {
                    if (input[1] < 52.652) {
                        var6 = 13848.59;
                    } else {
                        var6 = 3250.616;
                    }
                }
            }
        } else {
            if (input[1] < 60.40199) {
                if (input[3] < 32.860783) {
                    if (input[3] < 20.0) {
                        var6 = 10654.323;
                    } else {
                        var6 = -4561.799;
                    }
                } else {
                    if (input[2] < 77.703125) {
                        var6 = 16791.842;
                    } else {
                        var6 = -6910.2954;
                    }
                }
            } else {
                if (input[3] < 24.783726) {
                    if (input[1] < 67.83273) {
                        var6 = -3429.631;
                    } else {
                        var6 = 10475.136;
                    }
                } else {
                    if (input[2] < 100.0) {
                        var6 = 20177.723;
                    } else {
                        var6 = 0.6599121;
                    }
                }
            }
        }
    }
    float var7;
    if (input[4] < 75.03859) {
        if (input[0] < 100.60943) {
            if (input[4] < 36.52781) {
                if (input[5] < 6.878) {
                    var7 = -10892.893;
                } else {
                    var7 = -8452.1;
                }
            } else {
                if (input[4] < 55.17911) {
                    if (input[1] < 36.643) {
                        var7 = 8846.513;
                    } else {
                        var7 = -3076.398;
                    }
                } else {
                    if (input[1] < 48.208) {
                        var7 = -5802.714;
                    } else {
                        var7 = -630.6759;
                    }
                }
            }
        } else {
            if (input[1] < 29.71358) {
                if (input[4] < 56.682) {
                    if (input[4] < 50.356) {
                        var7 = -7357.493;
                    } else {
                        var7 = 2642.08;
                    }
                } else {
                    if (input[5] < 7.3248634) {
                        var7 = 10996.547;
                    } else {
                        var7 = -8189.293;
                    }
                }
            } else {
                if (input[2] < 100.0) {
                    if (input[4] < 61.987488) {
                        var7 = -3557.678;
                    } else {
                        var7 = 3050.9277;
                    }
                } else {
                    if (input[2] < 222.8815) {
                        var7 = 7241.2544;
                    } else {
                        var7 = -5308.2314;
                    }
                }
            }
        }
    } else {
        if (input[0] < 57.0) {
            if (input[1] < 35.0) {
                if (input[4] < 81.52184) {
                    if (input[0] < 15.245295) {
                        var7 = 8177.9;
                    } else {
                        var7 = -9309.283;
                    }
                } else {
                    if (input[2] < 106.0) {
                        var7 = 16853.557;
                    } else {
                        var7 = -5272.7954;
                    }
                }
            } else {
                if (input[3] < 29.725504) {
                    if (input[2] < 25.283222) {
                        var7 = -10962.729;
                    } else {
                        var7 = 4023.9578;
                    }
                } else {
                    if (input[1] < 77.32301) {
                        var7 = 15969.706;
                    } else {
                        var7 = -8208.94;
                    }
                }
            }
        } else {
            if (input[1] < 60.40199) {
                if (input[3] < 33.04688) {
                    if (input[0] < 155.0) {
                        var7 = -3798.8604;
                    } else {
                        var7 = 16478.494;
                    }
                } else {
                    if (input[5] < 6.7) {
                        var7 = 709.7455;
                    } else {
                        var7 = 19357.6;
                    }
                }
            } else {
                if (input[3] < 24.052162) {
                    if (input[1] < 76.129616) {
                        var7 = -1466.8297;
                    } else {
                        var7 = 13393.194;
                    }
                } else {
                    if (input[2] < 100.0) {
                        var7 = 17177.67;
                    } else {
                        var7 = -1007.52985;
                    }
                }
            }
        }
    }
    float var8;
    if (input[4] < 89.236465) {
        if (input[2] < 40.27596) {
            if (input[4] < 67.18) {
                if (input[4] < 58.5967) {
                    if (input[2] < 25.0) {
                        var8 = -3793.102;
                    } else {
                        var8 = 6412.627;
                    }
                } else {
                    if (input[2] < 3.0) {
                        var8 = -1238.4983;
                    } else {
                        var8 = -6356.9106;
                    }
                }
            } else {
                if (input[1] < 71.206) {
                    if (input[3] < 23.318535) {
                        var8 = 5043.8154;
                    } else {
                        var8 = -2107.9507;
                    }
                } else {
                    if (input[3] < 23.513252) {
                        var8 = -14337.524;
                    } else {
                        var8 = 13894.141;
                    }
                }
            }
        } else {
            if (input[3] < 26.286404) {
                if (input[5] < 6.522) {
                    if (input[0] < 12.538848) {
                        var8 = 5802.4873;
                    } else {
                        var8 = -799.3471;
                    }
                } else {
                    if (input[5] < 6.9960284) {
                        var8 = -5950.7505;
                    } else {
                        var8 = -1822.6438;
                    }
                }
            } else {
                if (input[5] < 6.866002) {
                    if (input[1] < 71.0) {
                        var8 = 2316.7295;
                    } else {
                        var8 = 8729.279;
                    }
                } else {
                    if (input[3] < 39.3005) {
                        var8 = -2395.2764;
                    } else {
                        var8 = 26045.81;
                    }
                }
            }
        }
    } else {
        if (input[0] < 73.87512) {
            if (input[2] < 107.78973) {
                if (input[4] < 91.70293) {
                    if (input[1] < 69.063) {
                        var8 = 11664.025;
                    } else {
                        var8 = -2684.2476;
                    }
                } else {
                    if (input[3] < 25.028496) {
                        var8 = 11476.363;
                    } else {
                        var8 = 15788.132;
                    }
                }
            } else {
                if (input[0] < 57.0) {
                    if (input[3] < 27.141937) {
                        var8 = 2164.527;
                    } else {
                        var8 = 16558.982;
                    }
                } else {
                    if (input[5] < 7.052329) {
                        var8 = -11248.986;
                    } else {
                        var8 = 85.03125;
                    }
                }
            }
        } else {
            if (input[3] < 33.5615) {
                if (input[3] < 32.26) {
                    if (input[3] < 25.226362) {
                        var8 = 286.15552;
                    } else {
                        var8 = -3623.0813;
                    }
                } else {
                    if (input[1] < 23.0) {
                        var8 = -20049.148;
                    } else {
                        var8 = -4715.1226;
                    }
                }
            } else {
                var8 = 15780.401;
            }
        }
    }
    float var9;
    if (input[4] < 75.03859) {
        if (input[3] < 26.023048) {
            if (input[4] < 46.97937) {
                if (input[1] < 43.0) {
                    if (input[4] < 41.51) {
                        var9 = 34907.41;
                    } else {
                        var9 = -6543.9736;
                    }
                } else {
                    if (input[2] < 82.6431) {
                        var9 = -9329.2;
                    } else {
                        var9 = -5019.8105;
                    }
                }
            } else {
                if (input[1] < 42.0) {
                    if (input[5] < 5.663428) {
                        var9 = 58.588024;
                    } else {
                        var9 = -5296.5674;
                    }
                } else {
                    if (input[5] < 7.3248634) {
                        var9 = -542.22424;
                    } else {
                        var9 = -3999.4353;
                    }
                }
            }
        } else {
            if (input[5] < 6.92753) {
                if (input[1] < 29.27178) {
                    if (input[4] < 55.17911) {
                        var9 = 14766.466;
                    } else {
                        var9 = 4226.185;
                    }
                } else {
                    if (input[2] < 120.0) {
                        var9 = -958.9247;
                    } else {
                        var9 = 4150.879;
                    }
                }
            } else {
                if (input[0] < 57.70576) {
                    if (input[1] < 74.361) {
                        var9 = -7445.6357;
                    } else {
                        var9 = 3631.9314;
                    }
                } else {
                    if (input[1] < 23.0) {
                        var9 = 8286.465;
                    } else {
                        var9 = -2276.2646;
                    }
                }
            }
        }
    } else {
        if (input[0] < 57.0) {
            if (input[2] < 89.88595) {
                if (input[1] < 35.0) {
                    if (input[4] < 81.52184) {
                        var9 = 444.73273;
                    } else {
                        var9 = 12671.224;
                    }
                } else {
                    if (input[2] < 25.283222) {
                        var9 = -4945.745;
                    } else {
                        var9 = 11854.27;
                    }
                }
            } else {
                if (input[4] < 83.83626) {
                    if (input[5] < 6.8539267) {
                        var9 = -6472.856;
                    } else {
                        var9 = 4579.6826;
                    }
                } else {
                    if (input[5] < 6.902751) {
                        var9 = 2326.373;
                    } else {
                        var9 = -11670.04;
                    }
                }
            }
        } else {
            if (input[1] < 64.764984) {
                if (input[3] < 34.1759) {
                    if (input[5] < 5.7405553) {
                        var9 = 6411.2866;
                    } else {
                        var9 = -3085.8997;
                    }
                } else {
                    if (input[2] < 110.0) {
                        var9 = 14997.833;
                    } else {
                        var9 = -8270.27;
                    }
                }
            } else {
                if (input[0] < 147.0) {
                    if (input[0] < 65.80163) {
                        var9 = -4708.144;
                    } else {
                        var9 = 14507.747;
                    }
                } else {
                    if (input[0] < 152.0) {
                        var9 = -27009.066;
                    } else {
                        var9 = 5126.6997;
                    }
                }
            }
        }
    }
    float var10;
    if (input[4] < 75.03859) {
        if (input[3] < 26.608786) {
            if (input[4] < 46.97937) {
                if (input[1] < 43.0) {
                    if (input[4] < 41.51) {
                        var10 = 33534.996;
                    } else {
                        var10 = -5651.6143;
                    }
                } else {
                    if (input[0] < 69.89587) {
                        var10 = -7587.824;
                    } else {
                        var10 = -12699.86;
                    }
                }
            } else {
                if (input[1] < 42.0) {
                    if (input[5] < 5.663428) {
                        var10 = -140.51709;
                    } else {
                        var10 = -4507.5303;
                    }
                } else {
                    if (input[5] < 6.593335) {
                        var10 = 297.41037;
                    } else {
                        var10 = -2219.6501;
                    }
                }
            }
        } else {
            if (input[5] < 6.92753) {
                if (input[1] < 29.27178) {
                    if (input[4] < 55.17911) {
                        var10 = 13641.88;
                    } else {
                        var10 = 4031.8438;
                    }
                } else {
                    if (input[1] < 73.0) {
                        var10 = -734.3922;
                    } else {
                        var10 = 4592.962;
                    }
                }
            } else {
                if (input[0] < 49.930733) {
                    if (input[1] < 65.19307) {
                        var10 = -7425.2104;
                    } else {
                        var10 = 549.93646;
                    }
                } else {
                    if (input[1] < 16.088) {
                        var10 = 9331.096;
                    } else {
                        var10 = -1752.6942;
                    }
                }
            }
        }
    } else {
        if (input[0] < 57.0) {
            if (input[2] < 89.88595) {
                if (input[1] < 35.0) {
                    if (input[4] < 81.52184) {
                        var10 = 380.49408;
                    } else {
                        var10 = 10773.959;
                    }
                } else {
                    if (input[2] < 25.283222) {
                        var10 = -4211.0156;
                    } else {
                        var10 = 10086.174;
                    }
                }
            } else {
                if (input[4] < 85.965385) {
                    if (input[3] < 25.54217) {
                        var10 = -3329.972;
                    } else {
                        var10 = -7335.0693;
                    }
                } else {
                    if (input[1] < 52.652) {
                        var10 = 9122.453;
                    } else {
                        var10 = 1507.8528;
                    }
                }
            }
        } else {
            if (input[1] < 64.764984) {
                if (input[3] < 34.1759) {
                    if (input[5] < 5.685225) {
                        var10 = 5952.04;
                    } else {
                        var10 = -2600.8872;
                    }
                } else {
                    if (input[2] < 110.0) {
                        var10 = 12820.727;
                    } else {
                        var10 = -7184.797;
                    }
                }
            } else {
                if (input[2] < 77.703125) {
                    if (input[5] < 7.1054306) {
                        var10 = 13097.665;
                    } else {
                        var10 = -9639.4375;
                    }
                } else {
                    if (input[2] < 181.15967) {
                        var10 = -3398.1282;
                    } else {
                        var10 = 18674.674;
                    }
                }
            }
        }
    }
    float var11;
    if (input[4] < 66.918205) {
        if (input[2] < 64.48997) {
            if (input[4] < 55.17911) {
                if (input[1] < 36.643) {
                    if (input[5] < 5.4751086) {
                        var11 = 28103.35;
                    } else {
                        var11 = 3231.0005;
                    }
                } else {
                    if (input[4] < 45.26633) {
                        var11 = -7185.8345;
                    } else {
                        var11 = 12.541619;
                    }
                }
            } else {
                if (input[1] < 84.0) {
                    if (input[2] < 37.763836) {
                        var11 = -3931.4382;
                    } else {
                        var11 = -1823.7601;
                    }
                } else {
                    if (input[3] < 27.955414) {
                        var11 = 17428.48;
                    } else {
                        var11 = -2532.105;
                    }
                }
            }
        } else {
            if (input[2] < 222.8815) {
                if (input[4] < 58.736168) {
                    if (input[0] < 148.22476) {
                        var11 = -1136.8269;
                    } else {
                        var11 = -8075.8203;
                    }
                } else {
                    if (input[1] < 71.86359) {
                        var11 = 2529.0464;
                    } else {
                        var11 = 9769.731;
                    }
                }
            } else {
                if (input[4] < 66.393) {
                    if (input[3] < 28.421057) {
                        var11 = -2128.0317;
                    } else {
                        var11 = -6784.492;
                    }
                } else {
                    if (input[0] < 105.521385) {
                        var11 = 19288.86;
                    } else {
                        var11 = 2128.9055;
                    }
                }
            }
        }
    } else {
        if (input[4] < 91.70293) {
            if (input[1] < 61.141) {
                if (input[0] < 48.0) {
                    if (input[1] < 40.0) {
                        var11 = 6718.3804;
                    } else {
                        var11 = -2018.7169;
                    }
                } else {
                    if (input[3] < 28.903) {
                        var11 = -3163.568;
                    } else {
                        var11 = 3882.371;
                    }
                }
            } else {
                if (input[0] < 64.0) {
                    if (input[4] < 83.83626) {
                        var11 = -4393.406;
                    } else {
                        var11 = 4323.2554;
                    }
                } else {
                    if (input[0] < 145.0) {
                        var11 = 9988.094;
                    } else {
                        var11 = -10687.005;
                    }
                }
            }
        } else {
            if (input[0] < 82.0) {
                if (input[2] < 110.0) {
                    if (input[2] < 14.318071) {
                        var11 = 11708.217;
                    } else {
                        var11 = 8337.042;
                    }
                } else {
                    if (input[1] < 63.86) {
                        var11 = -16075.666;
                    } else {
                        var11 = 1695.7534;
                    }
                }
            } else {
                if (input[1] < 54.33) {
                    if (input[3] < 32.26) {
                        var11 = -2094.7996;
                    } else {
                        var11 = -9499.477;
                    }
                } else {
                    if (input[2] < 84.0) {
                        var11 = 13326.653;
                    } else {
                        var11 = -7792.8555;
                    }
                }
            }
        }
    }
    float var12;
    if (input[4] < 66.918205) {
        if (input[2] < 64.48997) {
            if (input[5] < 7.5546823) {
                if (input[4] < 55.17911) {
                    if (input[1] < 36.643) {
                        var12 = 6522.509;
                    } else {
                        var12 = -1834.0057;
                    }
                } else {
                    if (input[2] < 1.2852505) {
                        var12 = 287.73264;
                    } else {
                        var12 = -2856.0564;
                    }
                }
            } else {
                if (input[1] < 76.805) {
                    if (input[4] < 59.880405) {
                        var12 = -10457.894;
                    } else {
                        var12 = -5909.499;
                    }
                } else {
                    if (input[0] < 58.46179) {
                        var12 = 30768.256;
                    } else {
                        var12 = 8124.6;
                    }
                }
            }
        } else {
            if (input[2] < 222.8815) {
                if (input[0] < 116.36958) {
                    if (input[1] < 80.994) {
                        var12 = -897.22723;
                    } else {
                        var12 = 7958.137;
                    }
                } else {
                    if (input[2] < 167.9841) {
                        var12 = 2752.933;
                    } else {
                        var12 = 11619.923;
                    }
                }
            } else {
                if (input[1] < 76.129616) {
                    if (input[4] < 65.76002) {
                        var12 = -3276.0305;
                    } else {
                        var12 = 14755.122;
                    }
                } else {
                    if (input[3] < 27.824) {
                        var12 = -2341.475;
                    } else {
                        var12 = -7489.6562;
                    }
                }
            }
        }
    } else {
        if (input[4] < 91.70293) {
            if (input[5] < 5.923549) {
                if (input[0] < 80.0) {
                    if (input[2] < 20.337639) {
                        var12 = -5792.982;
                    } else {
                        var12 = 2342.696;
                    }
                } else {
                    if (input[3] < 24.348202) {
                        var12 = -7338.9575;
                    } else {
                        var12 = 12184.955;
                    }
                }
            } else {
                if (input[3] < 41.382507) {
                    if (input[2] < 14.318071) {
                        var12 = 3428.525;
                    } else {
                        var12 = -470.35153;
                    }
                } else {
                    if (input[4] < 90.10853) {
                        var12 = 22154.262;
                    } else {
                        var12 = 5926.3096;
                    }
                }
            }
        } else {
            if (input[0] < 73.87512) {
                if (input[2] < 110.0) {
                    if (input[3] < 25.028496) {
                        var12 = 5331.0996;
                    } else {
                        var12 = 9161.616;
                    }
                } else {
                    if (input[1] < 63.86) {
                        var12 = -14869.991;
                    } else {
                        var12 = 1443.2612;
                    }
                }
            } else {
                if (input[1] < 39.235302) {
                    if (input[3] < 32.26) {
                        var12 = -1754.5125;
                    } else {
                        var12 = -8549.528;
                    }
                } else {
                    if (input[5] < 5.769785) {
                        var12 = -14782.496;
                    } else {
                        var12 = 13129.551;
                    }
                }
            }
        }
    }
    float var13;
    if (input[4] < 86.36511) {
        if (input[0] < 96.0) {
            if (input[1] < 65.19307) {
                if (input[5] < 5.859543) {
                    if (input[3] < 31.220695) {
                        var13 = -560.1455;
                    } else {
                        var13 = 8915.6455;
                    }
                } else {
                    if (input[2] < 45.0) {
                        var13 = -2993.1943;
                    } else {
                        var13 = -955.2132;
                    }
                }
            } else {
                if (input[0] < 61.47865) {
                    if (input[4] < 47.741) {
                        var13 = -5961.9766;
                    } else {
                        var13 = -244.40074;
                    }
                } else {
                    if (input[5] < 6.878) {
                        var13 = 9004.522;
                    } else {
                        var13 = -1196.0596;
                    }
                }
            }
        } else {
            if (input[5] < 6.803) {
                if (input[2] < 216.89438) {
                    if (input[1] < 72.38624) {
                        var13 = 1965.0831;
                    } else {
                        var13 = 6705.101;
                    }
                } else {
                    if (input[3] < 29.180365) {
                        var13 = -5258.551;
                    } else {
                        var13 = -496.6722;
                    }
                }
            } else {
                if (input[1] < 23.0) {
                    if (input[4] < 64.19913) {
                        var13 = 10230.269;
                    } else {
                        var13 = -4941.59;
                    }
                } else {
                    if (input[2] < 171.74876) {
                        var13 = -3094.658;
                    } else {
                        var13 = 1989.2385;
                    }
                }
            }
        }
    } else {
        if (input[0] < 69.89587) {
            if (input[2] < 88.0) {
                if (input[5] < 6.891) {
                    if (input[1] < 77.32301) {
                        var13 = 7401.4697;
                    } else {
                        var13 = -17380.521;
                    }
                } else {
                    if (input[2] < 14.318071) {
                        var13 = 7673.4995;
                    } else {
                        var13 = 463.48148;
                    }
                }
            } else {
                if (input[5] < 6.902751) {
                    if (input[4] < 87.784645) {
                        var13 = 9733.954;
                    } else {
                        var13 = 878.006;
                    }
                } else {
                    if (input[0] < 25.0) {
                        var13 = -20026.504;
                    } else {
                        var13 = 1223.6558;
                    }
                }
            }
        } else {
            if (input[3] < 22.812275) {
                if (input[2] < 1.2852505) {
                    var13 = 32594.621;
                } else {
                    if (input[5] < 6.535717) {
                        var13 = 4207.7593;
                    } else {
                        var13 = -1398.9985;
                    }
                }
            } else {
                if (input[1] < 49.0) {
                    if (input[0] < 75.368835) {
                        var13 = -7287.865;
                    } else {
                        var13 = -1948.7026;
                    }
                } else {
                    if (input[5] < 5.769785) {
                        var13 = -14033.36;
                    } else {
                        var13 = 4625.3877;
                    }
                }
            }
        }
    }
    float var14;
    if (input[4] < 66.918205) {
        if (input[3] < 27.200565) {
            if (input[4] < 46.97937) {
                if (input[1] < 43.0) {
                    if (input[4] < 41.51) {
                        var14 = 15112.454;
                    } else {
                        var14 = -3611.2932;
                    }
                } else {
                    if (input[4] < 36.52781) {
                        var14 = -4565.6846;
                    } else {
                        var14 = -7840.4917;
                    }
                }
            } else {
                if (input[1] < 44.0) {
                    if (input[0] < 160.75858) {
                        var14 = -2676.3157;
                    } else {
                        var14 = 11990.168;
                    }
                } else {
                    if (input[0] < 82.484764) {
                        var14 = 1370.3368;
                    } else {
                        var14 = -1923.0844;
                    }
                }
            }
        } else {
            if (input[1] < 34.321) {
                if (input[5] < 7.2001877) {
                    if (input[0] < 23.965307) {
                        var14 = 11905.059;
                    } else {
                        var14 = 3068.5215;
                    }
                } else {
                    if (input[3] < 29.497864) {
                        var14 = -1073.0581;
                    } else {
                        var14 = -9754.989;
                    }
                }
            } else {
                if (input[2] < 97.0) {
                    if (input[2] < 14.318071) {
                        var14 = 1884.2867;
                    } else {
                        var14 = -2973.9885;
                    }
                } else {
                    if (input[2] < 222.8815) {
                        var14 = 4476.3916;
                    } else {
                        var14 = -3922.038;
                    }
                }
            }
        }
    } else {
        if (input[2] < 77.703125) {
            if (input[1] < 68.776) {
                if (input[0] < 49.03933) {
                    if (input[1] < 40.0) {
                        var14 = 5892.417;
                    } else {
                        var14 = 271.43195;
                    }
                } else {
                    if (input[3] < 32.860783) {
                        var14 = -974.9567;
                    } else {
                        var14 = 7081.871;
                    }
                }
            } else {
                if (input[3] < 29.94138) {
                    if (input[5] < 7.1054306) {
                        var14 = 9979.077;
                    } else {
                        var14 = -6487.4497;
                    }
                } else {
                    if (input[5] < 6.0864987) {
                        var14 = -11941.928;
                    } else {
                        var14 = 457.88715;
                    }
                }
            }
        } else {
            if (input[3] < 31.094688) {
                if (input[3] < 20.466938) {
                    if (input[4] < 76.173) {
                        var14 = -11500.544;
                    } else {
                        var14 = -1981.6974;
                    }
                } else {
                    if (input[4] < 68.74849) {
                        var14 = 9872.265;
                    } else {
                        var14 = 8.813244;
                    }
                }
            } else {
                if (input[4] < 73.277) {
                    if (input[0] < 140.0) {
                        var14 = -11391.447;
                    } else {
                        var14 = 14057.958;
                    }
                } else {
                    if (input[2] < 89.88595) {
                        var14 = 9066.513;
                    } else {
                        var14 = -4329.735;
                    }
                }
            }
        }
    }
    float var15;
    if (input[4] < 89.236465) {
        if (input[0] < 96.0) {
            if (input[1] < 61.141) {
                if (input[4] < 52.008) {
                    if (input[1] < 46.0) {
                        var15 = 6557.8574;
                    } else {
                        var15 = -4208.371;
                    }
                } else {
                    if (input[2] < 44.836075) {
                        var15 = -2505.7922;
                    } else {
                        var15 = -595.47815;
                    }
                }
            } else {
                if (input[0] < 61.47865) {
                    if (input[4] < 47.741) {
                        var15 = -4538.118;
                    } else {
                        var15 = 339.0875;
                    }
                } else {
                    if (input[5] < 6.679226) {
                        var15 = 6862.2563;
                    } else {
                        var15 = -200.38388;
                    }
                }
            }
        } else {
            if (input[2] < 265.0) {
                if (input[3] < 26.97982) {
                    if (input[5] < 6.6590166) {
                        var15 = 886.8023;
                    } else {
                        var15 = -2464.0337;
                    }
                } else {
                    if (input[3] < 29.98716) {
                        var15 = 4562.2207;
                    } else {
                        var15 = -330.29602;
                    }
                }
            } else {
                if (input[3] < 25.866056) {
                    if (input[5] < 7.121625) {
                        var15 = 3107.177;
                    } else {
                        var15 = -2955.5107;
                    }
                } else {
                    if (input[5] < 5.663428) {
                        var15 = -801.34375;
                    } else {
                        var15 = -4819.862;
                    }
                }
            }
        }
    } else {
        if (input[0] < 73.87512) {
            if (input[2] < 107.78973) {
                if (input[3] < 24.971786) {
                    if (input[0] < 68.0) {
                        var15 = 2358.6682;
                    } else {
                        var15 = 24462.633;
                    }
                } else {
                    if (input[5] < 7.3462987) {
                        var15 = 6273.0957;
                    } else {
                        var15 = -83.44351;
                    }
                }
            } else {
                if (input[0] < 57.0) {
                    if (input[3] < 27.141937) {
                        var15 = 612.71356;
                    } else {
                        var15 = 13299.772;
                    }
                } else {
                    if (input[5] < 6.56062) {
                        var15 = -12563.422;
                    } else {
                        var15 = -1786.0996;
                    }
                }
            }
        } else {
            if (input[5] < 7.2437754) {
                if (input[5] < 5.769785) {
                    if (input[0] < 126.0) {
                        var15 = -10894.73;
                    } else {
                        var15 = 503.13284;
                    }
                } else {
                    if (input[2] < 43.0) {
                        var15 = 2383.1653;
                    } else {
                        var15 = -1495.5647;
                    }
                }
            } else {
                if (input[2] < 1.0) {
                    var15 = 2195.815;
                } else {
                    if (input[0] < 98.72169) {
                        var15 = -17717.592;
                    } else {
                        var15 = -3744.5298;
                    }
                }
            }
        }
    }
    float var16;
    if (input[4] < 66.918205) {
        if (input[5] < 7.639435) {
            if (input[3] < 27.200565) {
                if (input[5] < 4.6993885) {
                    if (input[1] < 5.729007) {
                        var16 = 8793.251;
                    } else {
                        var16 = -12183.664;
                    }
                } else {
                    if (input[1] < 14.70586) {
                        var16 = -4839.8276;
                    } else {
                        var16 = -1091.0308;
                    }
                }
            } else {
                if (input[1] < 24.431189) {
                    if (input[2] < 18.0) {
                        var16 = -3037.2915;
                    } else {
                        var16 = 6166.5786;
                    }
                } else {
                    if (input[0] < 6.0) {
                        var16 = 8894.35;
                    } else {
                        var16 = -552.5047;
                    }
                }
            }
        } else {
            if (input[1] < 79.52621) {
                if (input[3] < 22.486153) {
                    if (input[3] < 15.0) {
                        var16 = 4202.056;
                    } else {
                        var16 = -2212.342;
                    }
                } else {
                    if (input[0] < 104.0) {
                        var16 = -7292.2812;
                    } else {
                        var16 = -1454.9945;
                    }
                }
            } else {
                if (input[3] < 25.028496) {
                    if (input[0] < 58.46179) {
                        var16 = 25472.26;
                    } else {
                        var16 = 9299.07;
                    }
                } else {
                    if (input[1] < 80.13198) {
                        var16 = 2361.349;
                    } else {
                        var16 = -4021.2893;
                    }
                }
            }
        }
    } else {
        if (input[2] < 77.703125) {
            if (input[1] < 68.776) {
                if (input[0] < 49.03933) {
                    if (input[1] < 40.0) {
                        var16 = 4629.6416;
                    } else {
                        var16 = 24.636929;
                    }
                } else {
                    if (input[4] < 70.922066) {
                        var16 = 4936.938;
                    } else {
                        var16 = -972.2343;
                    }
                }
            } else {
                if (input[3] < 29.556324) {
                    if (input[3] < 24.409006) {
                        var16 = -2214.947;
                    } else {
                        var16 = 8734.305;
                    }
                } else {
                    if (input[1] < 69.063) {
                        var16 = 21128.143;
                    } else {
                        var16 = -3557.9104;
                    }
                }
            }
        } else {
            if (input[1] < 55.0) {
                if (input[2] < 181.15967) {
                    if (input[1] < 21.19562) {
                        var16 = 1166.715;
                    } else {
                        var16 = -5826.798;
                    }
                } else {
                    if (input[0] < 110.15318) {
                        var16 = -1827.1823;
                    } else {
                        var16 = 17911.453;
                    }
                }
            } else {
                if (input[1] < 67.17015) {
                    if (input[5] < 6.606674) {
                        var16 = 14768.91;
                    } else {
                        var16 = -1153.4565;
                    }
                } else {
                    if (input[2] < 135.0) {
                        var16 = -5032.9434;
                    } else {
                        var16 = 139.78015;
                    }
                }
            }
        }
    }
    float var17;
    if (input[4] < 91.70293) {
        if (input[4] < 45.26633) {
            if (input[0] < 152.0) {
                if (input[1] < 39.915737) {
                    if (input[5] < 6.4423933) {
                        var17 = 13390.187;
                    } else {
                        var17 = -5443.0576;
                    }
                } else {
                    if (input[3] < 25.28024) {
                        var17 = -2938.06;
                    } else {
                        var17 = -7416.969;
                    }
                }
            } else {
                if (input[2] < 1.0) {
                    var17 = -2587.9783;
                } else {
                    var17 = -19975.346;
                }
            }
        } else {
            if (input[5] < 6.866002) {
                if (input[3] < 25.376013) {
                    if (input[1] < 35.509106) {
                        var17 = -1864.268;
                    } else {
                        var17 = 59.795124;
                    }
                } else {
                    if (input[1] < 60.40199) {
                        var17 = 530.68823;
                    } else {
                        var17 = 3054.2754;
                    }
                }
            } else {
                if (input[3] < 19.346) {
                    if (input[1] < 75.70204) {
                        var17 = 1520.7717;
                    } else {
                        var17 = 18461.63;
                    }
                } else {
                    if (input[3] < 41.382507) {
                        var17 = -1614.9884;
                    } else {
                        var17 = 16781.338;
                    }
                }
            }
        }
    } else {
        if (input[0] < 82.0) {
            if (input[3] < 25.028496) {
                if (input[0] < 65.80163) {
                    if (input[2] < 20.337639) {
                        var17 = 4776.138;
                    } else {
                        var17 = -682.51965;
                    }
                } else {
                    if (input[3] < 22.306225) {
                        var17 = 5403.8623;
                    } else {
                        var17 = 23446.54;
                    }
                }
            } else {
                if (input[0] < 65.0) {
                    if (input[0] < 64.0) {
                        var17 = 4929.969;
                    } else {
                        var17 = 20800.775;
                    }
                } else {
                    if (input[1] < 38.77872) {
                        var17 = -5928.1357;
                    } else {
                        var17 = 5349.8154;
                    }
                }
            }
        } else {
            if (input[1] < 54.33) {
                if (input[3] < 23.601154) {
                    if (input[0] < 98.72169) {
                        var17 = 1446.5696;
                    } else {
                        var17 = 7384.2603;
                    }
                } else {
                    if (input[5] < 6.1211686) {
                        var17 = -3186.1072;
                    } else {
                        var17 = -630.7495;
                    }
                }
            } else {
                if (input[4] < 96.927864) {
                    if (input[1] < 57.919125) {
                        var17 = 14169.493;
                    } else {
                        var17 = 6089.2334;
                    }
                } else {
                    if (input[0] < 92.0) {
                        var17 = -5338.4253;
                    } else {
                        var17 = -23.081251;
                    }
                }
            }
        }
    }
    float var18;
    if (input[4] < 86.36511) {
        if (input[0] < 115.34102) {
            if (input[5] < 5.859543) {
                if (input[4] < 45.26633) {
                    if (input[1] < 17.38633) {
                        var18 = 17316.062;
                    } else {
                        var18 = -4103.9844;
                    }
                } else {
                    if (input[4] < 53.331158) {
                        var18 = 8597.981;
                    } else {
                        var18 = 671.5326;
                    }
                }
            } else {
                if (input[1] < 56.432) {
                    if (input[0] < 9.460898) {
                        var18 = 1376.5198;
                    } else {
                        var18 = -1830.6693;
                    }
                } else {
                    if (input[0] < 46.0) {
                        var18 = -1511.0895;
                    } else {
                        var18 = 1739.9862;
                    }
                }
            }
        } else {
            if (input[5] < 6.094) {
                if (input[1] < 70.363686) {
                    if (input[0] < 117.442154) {
                        var18 = 9800.48;
                    } else {
                        var18 = -3337.0657;
                    }
                } else {
                    if (input[5] < 5.714) {
                        var18 = 9174.504;
                    } else {
                        var18 = -2976.6382;
                    }
                }
            } else {
                if (input[5] < 6.191) {
                    if (input[2] < 209.09291) {
                        var18 = 12665.863;
                    } else {
                        var18 = -3250.2498;
                    }
                } else {
                    if (input[1] < 42.0) {
                        var18 = 4997.4326;
                    } else {
                        var18 = -90.23729;
                    }
                }
            }
        }
    } else {
        if (input[0] < 69.89587) {
            if (input[2] < 14.318071) {
                if (input[1] < 52.652) {
                    if (input[4] < 87.45126) {
                        var18 = 18777.275;
                    } else {
                        var18 = 5147.446;
                    }
                } else {
                    if (input[4] < 90.55484) {
                        var18 = -27333.74;
                    } else {
                        var18 = 9074.483;
                    }
                }
            } else {
                if (input[5] < 6.891) {
                    if (input[3] < 24.971786) {
                        var18 = 481.842;
                    } else {
                        var18 = 4515.7075;
                    }
                } else {
                    if (input[1] < 63.0) {
                        var18 = -3498.4236;
                    } else {
                        var18 = 8911.249;
                    }
                }
            }
        } else {
            if (input[3] < 22.199108) {
                if (input[0] < 109.686874) {
                    if (input[5] < 6.535717) {
                        var18 = 5705.017;
                    } else {
                        var18 = 374.21252;
                    }
                } else {
                    var18 = 28260.936;
                }
            } else {
                if (input[5] < 5.769785) {
                    if (input[0] < 77.16157) {
                        var18 = -19493.75;
                    } else {
                        var18 = -665.63794;
                    }
                } else {
                    if (input[5] < 7.2848873) {
                        var18 = -479.1705;
                    } else {
                        var18 = -8029.838;
                    }
                }
            }
        }
    }
    float var19;
    if (input[4] < 66.918205) {
        if (input[5] < 7.639435) {
            if (input[1] < 22.12907) {
                if (input[0] < 94.439064) {
                    if (input[5] < 5.076736) {
                        var19 = 14537.12;
                    } else {
                        var19 = -941.2924;
                    }
                } else {
                    if (input[4] < 50.356) {
                        var19 = -10858.029;
                    } else {
                        var19 = 6062.536;
                    }
                }
            } else {
                if (input[0] < 12.538848) {
                    if (input[3] < 32.128) {
                        var19 = -521.27014;
                    } else {
                        var19 = 12877.263;
                    }
                } else {
                    if (input[3] < 28.947046) {
                        var19 = -220.96498;
                    } else {
                        var19 = -1520.8363;
                    }
                }
            }
        } else {
            if (input[0] < 38.35763) {
                if (input[3] < 18.68) {
                    if (input[0] < 18.738323) {
                        var19 = 4886.8516;
                    } else {
                        var19 = -1095.1102;
                    }
                } else {
                    if (input[4] < 57.423) {
                        var19 = -7343.2466;
                    } else {
                        var19 = -3921.2205;
                    }
                }
            } else {
                if (input[3] < 27.079517) {
                    if (input[1] < 79.52621) {
                        var19 = -693.1295;
                    } else {
                        var19 = 14338.745;
                    }
                } else {
                    if (input[0] < 104.0) {
                        var19 = -6268.5576;
                    } else {
                        var19 = -1257.5454;
                    }
                }
            }
        }
    } else {
        if (input[5] < 5.812) {
            if (input[0] < 87.0) {
                if (input[3] < 29.840708) {
                    if (input[3] < 22.391308) {
                        var19 = -1858.7367;
                    } else {
                        var19 = 2972.378;
                    }
                } else {
                    if (input[0] < 28.737057) {
                        var19 = 5809.1733;
                    } else {
                        var19 = -11716.139;
                    }
                }
            } else {
                if (input[1] < 28.29886) {
                    if (input[3] < 32.41123) {
                        var19 = -7072.58;
                    } else {
                        var19 = 11178.503;
                    }
                } else {
                    if (input[3] < 24.348202) {
                        var19 = -8218.506;
                    } else {
                        var19 = 13895.289;
                    }
                }
            }
        } else {
            if (input[3] < 37.57273) {
                if (input[2] < 14.318071) {
                    if (input[0] < 127.804855) {
                        var19 = 1307.0526;
                    } else {
                        var19 = 11188.348;
                    }
                } else {
                    if (input[0] < 150.0) {
                        var19 = 26.366667;
                    } else {
                        var19 = -9059.651;
                    }
                }
            } else {
                if (input[4] < 73.89817) {
                    if (input[0] < 28.0) {
                        var19 = -13877.844;
                    } else {
                        var19 = -1622.1598;
                    }
                } else {
                    if (input[4] < 90.10853) {
                        var19 = 13280.761;
                    } else {
                        var19 = 3860.8787;
                    }
                }
            }
        }
    }
    float var20;
    if (input[4] < 86.36511) {
        if (input[0] < 115.34102) {
            if (input[1] < 65.19307) {
                if (input[4] < 52.008) {
                    if (input[1] < 46.0) {
                        var20 = 5192.7373;
                    } else {
                        var20 = -2252.0303;
                    }
                } else {
                    if (input[2] < 116.0) {
                        var20 = -937.26;
                    } else {
                        var20 = -3740.9353;
                    }
                }
            } else {
                if (input[0] < 61.47865) {
                    if (input[2] < 15.0) {
                        var20 = 4116.633;
                    } else {
                        var20 = -2243.1863;
                    }
                } else {
                    if (input[5] < 6.878) {
                        var20 = 4473.8467;
                    } else {
                        var20 = -2061.7014;
                    }
                }
            }
        } else {
            if (input[5] < 6.014854) {
                if (input[0] < 143.0) {
                    if (input[1] < 71.0) {
                        var20 = -1469.6604;
                    } else {
                        var20 = 6403.592;
                    }
                } else {
                    if (input[2] < 159.0) {
                        var20 = -6373.378;
                    } else {
                        var20 = -692.7229;
                    }
                }
            } else {
                if (input[5] < 6.803) {
                    if (input[1] < 80.13198) {
                        var20 = 4554.6206;
                    } else {
                        var20 = -3775.675;
                    }
                } else {
                    if (input[3] < 26.674065) {
                        var20 = -2807.9905;
                    } else {
                        var20 = 1055.7924;
                    }
                }
            }
        }
    } else {
        if (input[2] < 14.318071) {
            if (input[4] < 87.45126) {
                if (input[3] < 20.619783) {
                    var20 = 26521.72;
                } else {
                    if (input[0] < 28.737057) {
                        var20 = 12375.946;
                    } else {
                        var20 = -1732.5383;
                    }
                }
            } else {
                if (input[1] < 52.652) {
                    if (input[0] < 82.0) {
                        var20 = 4376.7246;
                    } else {
                        var20 = -2873.7668;
                    }
                } else {
                    if (input[4] < 90.55484) {
                        var20 = -23695.148;
                    } else {
                        var20 = 6512.5835;
                    }
                }
            }
        } else {
            if (input[0] < 73.0) {
                if (input[2] < 23.0) {
                    if (input[1] < 34.761) {
                        var20 = 2489.1545;
                    } else {
                        var20 = -13578.799;
                    }
                } else {
                    if (input[5] < 7.3462987) {
                        var20 = 2178.8164;
                    } else {
                        var20 = -7575.6514;
                    }
                }
            } else {
                if (input[0] < 141.0) {
                    if (input[3] < 33.04688) {
                        var20 = -908.8232;
                    } else {
                        var20 = 3836.093;
                    }
                } else {
                    if (input[1] < 17.0) {
                        var20 = 5731.8013;
                    } else {
                        var20 = -15906.274;
                    }
                }
            }
        }
    }
    float var21;
    if (input[4] < 45.26633) {
        if (input[0] < 152.0) {
            if (input[1] < 11.5815525) {
                if (input[3] < 22.979664) {
                    var21 = -2439.2263;
                } else {
                    var21 = -12722.922;
                }
            } else {
                if (input[1] < 39.915737) {
                    if (input[4] < 41.51) {
                        var21 = 19034.268;
                    } else {
                        var21 = 307.40308;
                    }
                } else {
                    if (input[3] < 25.28024) {
                        var21 = -1780.504;
                    } else {
                        var21 = -5792.997;
                    }
                }
            }
        } else {
            if (input[2] < 37.763836) {
                var21 = -5592.826;
            } else {
                var21 = -19112.512;
            }
        }
    } else {
        if (input[2] < 265.0) {
            if (input[1] < 56.432) {
                if (input[0] < 12.0) {
                    if (input[3] < 33.94) {
                        var21 = 1888.5891;
                    } else {
                        var21 = 14633.19;
                    }
                } else {
                    if (input[0] < 123.6427) {
                        var21 = -736.4447;
                    } else {
                        var21 = 1915.0848;
                    }
                }
            } else {
                if (input[0] < 39.0) {
                    if (input[2] < 15.0) {
                        var21 = 4691.6733;
                    } else {
                        var21 = -1603.6335;
                    }
                } else {
                    if (input[3] < 24.464146) {
                        var21 = -1163.2482;
                    } else {
                        var21 = 2439.141;
                    }
                }
            }
        } else {
            if (input[3] < 27.824) {
                if (input[5] < 7.038153) {
                    if (input[3] < 25.866056) {
                        var21 = 1850.867;
                    } else {
                        var21 = -3444.8723;
                    }
                } else {
                    if (input[2] < 332.74554) {
                        var21 = 4072.8997;
                    } else {
                        var21 = -1893.1027;
                    }
                }
            } else {
                if (input[5] < 5.663428) {
                    if (input[5] < 5.1338725) {
                        var21 = -4463.003;
                    } else {
                        var21 = 3429.305;
                    }
                } else {
                    if (input[4] < 68.10365) {
                        var21 = -4426.943;
                    } else {
                        var21 = 2817.143;
                    }
                }
            }
        }
    }
    float var22;
    if (input[4] < 86.36511) {
        if (input[2] < 222.8815) {
            if (input[2] < 167.9841) {
                if (input[1] < 86.0) {
                    if (input[5] < 6.4893894) {
                        var22 = 180.87303;
                    } else {
                        var22 = -867.6708;
                    }
                } else {
                    if (input[4] < 52.008) {
                        var22 = -6738.976;
                    } else {
                        var22 = 7721.287;
                    }
                }
            } else {
                if (input[0] < 119.3437) {
                    if (input[2] < 194.99553) {
                        var22 = 3147.1997;
                    } else {
                        var22 = -3964.6873;
                    }
                } else {
                    if (input[5] < 5.585289) {
                        var22 = -10278.591;
                    } else {
                        var22 = 11525.144;
                    }
                }
            }
        } else {
            if (input[3] < 27.49888) {
                if (input[1] < 46.697334) {
                    if (input[5] < 6.221763) {
                        var22 = -3930.4216;
                    } else {
                        var22 = 19416.719;
                    }
                } else {
                    if (input[4] < 64.3835) {
                        var22 = -899.7579;
                    } else {
                        var22 = 3875.6902;
                    }
                }
            } else {
                if (input[3] < 29.357) {
                    if (input[4] < 53.937) {
                        var22 = 6517.315;
                    } else {
                        var22 = -4630.494;
                    }
                } else {
                    if (input[4] < 80.18547) {
                        var22 = -684.4645;
                    } else {
                        var22 = 17250.3;
                    }
                }
            }
        }
    } else {
        if (input[0] < 69.0) {
            if (input[0] < 25.0) {
                if (input[1] < 38.77872) {
                    if (input[4] < 89.236465) {
                        var22 = 7775.826;
                    } else {
                        var22 = 2192.468;
                    }
                } else {
                    if (input[1] < 63.86) {
                        var22 = -18631.527;
                    } else {
                        var22 = 623.15845;
                    }
                }
            } else {
                if (input[3] < 24.269571) {
                    if (input[0] < 55.348637) {
                        var22 = 1661.0494;
                    } else {
                        var22 = -16819.166;
                    }
                } else {
                    if (input[3] < 24.783726) {
                        var22 = 11576.148;
                    } else {
                        var22 = 3277.39;
                    }
                }
            }
        } else {
            if (input[3] < 22.906) {
                if (input[2] < 1.2852505) {
                    var22 = 22687.969;
                } else {
                    if (input[0] < 73.0) {
                        var22 = 10332.328;
                    } else {
                        var22 = 873.1701;
                    }
                }
            } else {
                if (input[5] < 6.205238) {
                    if (input[0] < 77.16157) {
                        var22 = -10881.479;
                    } else {
                        var22 = -1476.601;
                    }
                } else {
                    if (input[1] < 42.585133) {
                        var22 = -926.2066;
                    } else {
                        var22 = 3424.3267;
                    }
                }
            }
        }
    }
    float var23;
    if (input[4] < 43.653053) {
        if (input[4] < 41.51) {
            if (input[1] < 44.0) {
                if (input[3] < 26.286404) {
                    var23 = 26233.236;
                } else {
                    if (input[0] < 3.3448536) {
                        var23 = 22348.545;
                    } else {
                        var23 = -5483.7705;
                    }
                }
            } else {
                if (input[4] < 36.52781) {
                    if (input[2] < 10.0) {
                        var23 = -2975.7107;
                    } else {
                        var23 = -1388.9836;
                    }
                } else {
                    if (input[2] < 32.17012) {
                        var23 = -7688.3276;
                    } else {
                        var23 = 6653.3306;
                    }
                }
            }
        } else {
            if (input[3] < 37.57273) {
                if (input[3] < 21.62854) {
                    var23 = 1190.4973;
                } else {
                    if (input[1] < 80.994) {
                        var23 = -9111.528;
                    } else {
                        var23 = -683.36487;
                    }
                }
            } else {
                var23 = 6004.1953;
            }
        }
    } else {
        if (input[5] < 6.866002) {
            if (input[3] < 25.376013) {
                if (input[1] < 35.509106) {
                    if (input[0] < 35.735455) {
                        var23 = 439.52744;
                    } else {
                        var23 = -2146.5515;
                    }
                } else {
                    if (input[0] < 155.0) {
                        var23 = 161.53377;
                    } else {
                        var23 = 9770.61;
                    }
                }
            } else {
                if (input[2] < 216.89438) {
                    if (input[1] < 60.40199) {
                        var23 = 593.2328;
                    } else {
                        var23 = 2408.0508;
                    }
                } else {
                    if (input[5] < 6.83068) {
                        var23 = -2794.1042;
                    } else {
                        var23 = 18820.379;
                    }
                }
            }
        } else {
            if (input[3] < 22.486153) {
                if (input[1] < 80.994) {
                    if (input[1] < 28.0) {
                        var23 = 4413.1997;
                    } else {
                        var23 = -444.21234;
                    }
                } else {
                    if (input[5] < 7.2615433) {
                        var23 = 19634.947;
                    } else {
                        var23 = 356.37903;
                    }
                }
            } else {
                if (input[3] < 41.382507) {
                    if (input[0] < 39.0) {
                        var23 = -2387.3442;
                    } else {
                        var23 = -528.9939;
                    }
                } else {
                    if (input[4] < 96.927864) {
                        var23 = 13157.668;
                    } else {
                        var23 = 1158.6141;
                    }
                }
            }
        }
    }
    float var24;
    if (input[5] < 4.5161543) {
        if (input[3] < 31.094688) {
            if (input[1] < 80.994) {
                if (input[2] < 26.592365) {
                    if (input[2] < 25.283222) {
                        var24 = -10785.894;
                    } else {
                        var24 = -1097.0579;
                    }
                } else {
                    var24 = -16478.76;
                }
            } else {
                var24 = 12661.162;
            }
        } else {
            if (input[1] < 48.631) {
                var24 = 25286.594;
            } else {
                var24 = -5926.713;
            }
        }
    } else {
        if (input[4] < 91.70293) {
            if (input[3] < 41.382507) {
                if (input[2] < 40.27596) {
                    if (input[5] < 5.322044) {
                        var24 = 5323.4;
                    } else {
                        var24 = -673.7664;
                    }
                } else {
                    if (input[4] < 53.688843) {
                        var24 = -2134.9275;
                    } else {
                        var24 = 549.26355;
                    }
                }
            } else {
                if (input[4] < 88.30406) {
                    if (input[1] < 70.363686) {
                        var24 = 17251.453;
                    } else {
                        var24 = -1355.0508;
                    }
                } else {
                    if (input[0] < 43.347652) {
                        var24 = 5974.0293;
                    } else {
                        var24 = 1175.7391;
                    }
                }
            }
        } else {
            if (input[2] < 16.438295) {
                if (input[0] < 50.5445) {
                    if (input[1] < 34.0) {
                        var24 = 1523.9214;
                    } else {
                        var24 = 6107.934;
                    }
                } else {
                    if (input[0] < 82.0) {
                        var24 = 12047.932;
                    } else {
                        var24 = -222.44722;
                    }
                }
            } else {
                if (input[1] < 39.235302) {
                    if (input[3] < 25.028496) {
                        var24 = -3689.9167;
                    } else {
                        var24 = 997.9495;
                    }
                } else {
                    if (input[1] < 59.987083) {
                        var24 = 7467.2515;
                    } else {
                        var24 = 593.62274;
                    }
                }
            }
        }
    }
    float var25;
    if (input[5] < 4.5161543) {
        if (input[3] < 31.094688) {
            if (input[1] < 80.994) {
                if (input[2] < 26.592365) {
                    if (input[2] < 25.283222) {
                        var25 = -9248.903;
                    } else {
                        var25 = -1014.77814;
                    }
                } else {
                    if (input[2] < 216.89438) {
                        var25 = -14735.919;
                    } else {
                        var25 = -4230.02;
                    }
                }
            } else {
                var25 = 11395.046;
            }
        } else {
            if (input[1] < 48.631) {
                var25 = 22252.201;
            } else {
                var25 = -5482.209;
            }
        }
    } else {
        if (input[5] < 6.866002) {
            if (input[3] < 25.376013) {
                if (input[4] < 82.14809) {
                    if (input[3] < 18.897156) {
                        var25 = -2074.612;
                    } else {
                        var25 = -425.19534;
                    }
                } else {
                    if (input[0] < 123.6427) {
                        var25 = 592.8671;
                    } else {
                        var25 = 16108.937;
                    }
                }
            } else {
                if (input[0] < 5.272074) {
                    if (input[1] < 40.324883) {
                        var25 = 11188.118;
                    } else {
                        var25 = -2908.1318;
                    }
                } else {
                    if (input[3] < 29.98716) {
                        var25 = 1071.018;
                    } else {
                        var25 = -306.60504;
                    }
                }
            }
        } else {
            if (input[1] < 20.0) {
                if (input[5] < 7.1903377) {
                    if (input[4] < 56.88009) {
                        var25 = 13242.038;
                    } else {
                        var25 = 1892.3586;
                    }
                } else {
                    if (input[3] < 27.034096) {
                        var25 = 3287.8079;
                    } else {
                        var25 = -5788.5137;
                    }
                }
            } else {
                if (input[1] < 46.0) {
                    if (input[2] < 200.35768) {
                        var25 = -2076.0718;
                    } else {
                        var25 = 14869.973;
                    }
                } else {
                    if (input[0] < 80.0) {
                        var25 = 1110.9414;
                    } else {
                        var25 = -1163.0287;
                    }
                }
            }
        }
    }
    float var26;
    if (input[2] < 222.8815) {
        if (input[0] < 191.0) {
            if (input[0] < 180.8994) {
                if (input[2] < 167.9841) {
                    if (input[0] < 148.22476) {
                        var26 = 61.20769;
                    } else {
                        var26 = -2186.2378;
                    }
                } else {
                    if (input[0] < 119.3437) {
                        var26 = -408.41275;
                    } else {
                        var26 = 7069.1567;
                    }
                }
            } else {
                if (input[5] < 6.1510873) {
                    if (input[2] < 71.0) {
                        var26 = 8320.262;
                    } else {
                        var26 = -7948.508;
                    }
                } else {
                    var26 = 19451.652;
                }
            }
        } else {
            if (input[2] < 186.0) {
                if (input[1] < 42.0) {
                    if (input[1] < 10.736338) {
                        var26 = 3857.5127;
                    } else {
                        var26 = 15185.641;
                    }
                } else {
                    if (input[3] < 26.091282) {
                        var26 = -1765.3032;
                    } else {
                        var26 = -7499.7114;
                    }
                }
            } else {
                if (input[3] < 30.583355) {
                    var26 = -27478.309;
                } else {
                    var26 = -7513.6973;
                }
            }
        }
    } else {
        if (input[3] < 27.49888) {
            if (input[3] < 19.346) {
                if (input[2] < 242.0) {
                    var26 = -9552.557;
                } else {
                    if (input[0] < 23.031929) {
                        var26 = -1905.8356;
                    } else {
                        var26 = 1216.7297;
                    }
                }
            } else {
                if (input[1] < 46.697334) {
                    if (input[2] < 252.28195) {
                        var26 = 17295.363;
                    } else {
                        var26 = -893.7946;
                    }
                } else {
                    if (input[3] < 22.199108) {
                        var26 = 6105.7656;
                    } else {
                        var26 = -392.61197;
                    }
                }
            }
        } else {
            if (input[3] < 29.357) {
                if (input[4] < 53.937) {
                    if (input[1] < 45.21) {
                        var26 = 17875.873;
                    } else {
                        var26 = -1321.8032;
                    }
                } else {
                    if (input[2] < 242.0) {
                        var26 = -7593.7944;
                    } else {
                        var26 = -3093.7825;
                    }
                }
            } else {
                if (input[0] < 101.17893) {
                    if (input[5] < 4.992127) {
                        var26 = -1908.5045;
                    } else {
                        var26 = -7746.2266;
                    }
                } else {
                    if (input[4] < 66.393) {
                        var26 = 352.1057;
                    } else {
                        var26 = 22134.926;
                    }
                }
            }
        }
    }
    float var27;
    if (input[4] < 43.653053) {
        if (input[4] < 41.51) {
            if (input[1] < 44.0) {
                if (input[2] < 79.69791) {
                    if (input[5] < 6.5766764) {
                        var27 = 16744.457;
                    } else {
                        var27 = -6043.346;
                    }
                } else {
                    var27 = -15135.605;
                }
            } else {
                if (input[4] < 36.52781) {
                    if (input[2] < 10.0) {
                        var27 = -2405.2173;
                    } else {
                        var27 = -957.1127;
                    }
                } else {
                    if (input[2] < 32.17012) {
                        var27 = -6546.3267;
                    } else {
                        var27 = 6314.4307;
                    }
                }
            }
        } else {
            if (input[3] < 37.57273) {
                if (input[3] < 21.62854) {
                    var27 = 1302.8579;
                } else {
                    if (input[1] < 80.994) {
                        var27 = -7569.271;
                    } else {
                        var27 = -563.17505;
                    }
                }
            } else {
                var27 = 5732.405;
            }
        }
    } else {
        if (input[0] < 15.245295) {
            if (input[3] < 33.94) {
                if (input[1] < 44.0) {
                    if (input[4] < 58.426605) {
                        var27 = 8804.705;
                    } else {
                        var27 = 653.1291;
                    }
                } else {
                    if (input[3] < 26.737) {
                        var27 = 506.75504;
                    } else {
                        var27 = -4323.939;
                    }
                }
            } else {
                if (input[4] < 56.88009) {
                    if (input[2] < 31.964447) {
                        var27 = 22704.557;
                    } else {
                        var27 = 7108.174;
                    }
                } else {
                    if (input[4] < 62.15172) {
                        var27 = -6389.1655;
                    } else {
                        var27 = 8070.3477;
                    }
                }
            }
        } else {
            if (input[1] < 56.432) {
                if (input[0] < 122.460655) {
                    if (input[4] < 46.97937) {
                        var27 = 6309.089;
                    } else {
                        var27 = -628.0378;
                    }
                } else {
                    if (input[5] < 5.944756) {
                        var27 = -5061.8335;
                    } else {
                        var27 = 2857.7417;
                    }
                }
            } else {
                if (input[0] < 22.711555) {
                    if (input[3] < 29.602142) {
                        var27 = -2123.726;
                    } else {
                        var27 = -10567.036;
                    }
                } else {
                    if (input[0] < 148.22476) {
                        var27 = 1162.7172;
                    } else {
                        var27 = -2159.134;
                    }
                }
            }
        }
    }
    float var28;
    if (input[5] < 4.5161543) {
        if (input[3] < 31.094688) {
            if (input[1] < 80.994) {
                if (input[2] < 26.592365) {
                    if (input[2] < 25.283222) {
                        var28 = -7848.0845;
                    } else {
                        var28 = -992.2442;
                    }
                } else {
                    var28 = -12378.761;
                }
            } else {
                var28 = 9806.233;
            }
        } else {
            if (input[1] < 48.631) {
                var28 = 19269.738;
            } else {
                var28 = -4751.339;
            }
        }
    } else {
        if (input[5] < 6.866002) {
            if (input[3] < 25.428337) {
                if (input[0] < 155.0) {
                    if (input[0] < 152.0) {
                        var28 = -305.91348;
                    } else {
                        var28 = -11964.852;
                    }
                } else {
                    if (input[1] < 58.449) {
                        var28 = 17969.107;
                    } else {
                        var28 = -4026.8196;
                    }
                }
            } else {
                if (input[0] < 40.0) {
                    if (input[4] < 53.688843) {
                        var28 = 8963.222;
                    } else {
                        var28 = -67.97118;
                    }
                } else {
                    if (input[1] < 60.40199) {
                        var28 = -509.9763;
                    } else {
                        var28 = 1893.3162;
                    }
                }
            }
        } else {
            if (input[3] < 22.746216) {
                if (input[1] < 80.994) {
                    if (input[1] < 28.0) {
                        var28 = 3797.9036;
                    } else {
                        var28 = -303.08713;
                    }
                } else {
                    if (input[4] < 57.80249) {
                        var28 = 19098.863;
                    } else {
                        var28 = 1323.9708;
                    }
                }
            } else {
                if (input[3] < 22.979664) {
                    if (input[0] < 33.99768) {
                        var28 = -4937.877;
                    } else {
                        var28 = -13966.449;
                    }
                } else {
                    if (input[0] < 39.0) {
                        var28 = -1967.8363;
                    } else {
                        var28 = -195.08246;
                    }
                }
            }
        }
    }
    float var29;
    if (input[1] < 19.51048) {
        if (input[3] < 33.7315) {
            if (input[3] < 32.128) {
                if (input[1] < 15.899695) {
                    if (input[4] < 53.688843) {
                        var29 = -5368.983;
                    } else {
                        var29 = 563.7305;
                    }
                } else {
                    if (input[4] < 58.060223) {
                        var29 = 10830.715;
                    } else {
                        var29 = 994.35187;
                    }
                }
            } else {
                if (input[1] < 17.38633) {
                    if (input[2] < 167.9841) {
                        var29 = -9590.612;
                    } else {
                        var29 = 10359.5205;
                    }
                } else {
                    if (input[0] < 94.439064) {
                        var29 = -566.865;
                    } else {
                        var29 = 20851.312;
                    }
                }
            }
        } else {
            if (input[2] < 74.27537) {
                if (input[0] < 83.06356) {
                    if (input[2] < 40.27596) {
                        var29 = 8360.493;
                    } else {
                        var29 = -7225.233;
                    }
                } else {
                    if (input[0] < 113.0) {
                        var29 = 33490.312;
                    } else {
                        var29 = -2456.6997;
                    }
                }
            } else {
                if (input[0] < 96.0) {
                    if (input[2] < 104.0) {
                        var29 = -7241.129;
                    } else {
                        var29 = 1038.705;
                    }
                } else {
                    var29 = -20350.822;
                }
            }
        }
    } else {
        if (input[2] < 14.318071) {
            if (input[1] < 33.596798) {
                if (input[0] < 1.1725864) {
                    if (input[4] < 52.94) {
                        var29 = 21655.193;
                    } else {
                        var29 = 3245.0532;
                    }
                } else {
                    if (input[4] < 60.43509) {
                        var29 = -3113.747;
                    } else {
                        var29 = 319.8631;
                    }
                }
            } else {
                if (input[5] < 7.5546823) {
                    if (input[4] < 80.544044) {
                        var29 = 1951.847;
                    } else {
                        var29 = -2761.5022;
                    }
                } else {
                    if (input[3] < 29.133688) {
                        var29 = -5580.7217;
                    } else {
                        var29 = -675.6286;
                    }
                }
            }
        } else {
            if (input[2] < 25.697735) {
                if (input[3] < 25.0) {
                    if (input[1] < 84.0) {
                        var29 = 104.7471;
                    } else {
                        var29 = 19370.873;
                    }
                } else {
                    if (input[0] < 40.32462) {
                        var29 = -4220.4985;
                    } else {
                        var29 = -1097.6901;
                    }
                }
            } else {
                if (input[0] < 73.87512) {
                    if (input[3] < 19.095127) {
                        var29 = -2260.6245;
                    } else {
                        var29 = 952.46497;
                    }
                } else {
                    if (input[4] < 57.80249) {
                        var29 = -2852.8267;
                    } else {
                        var29 = -181.73877;
                    }
                }
            }
        }
    }
    float var30;
    if (input[4] < 43.653053) {
        if (input[4] < 41.51) {
            if (input[0] < 133.58269) {
                if (input[1] < 39.915737) {
                    if (input[5] < 5.9979987) {
                        var30 = -10627.646;
                    } else {
                        var30 = 13399.515;
                    }
                } else {
                    if (input[0] < 60.512794) {
                        var30 = -1476.7433;
                    } else {
                        var30 = 15002.023;
                    }
                }
            } else {
                var30 = -12184.301;
            }
        } else {
            if (input[3] < 37.57273) {
                if (input[5] < 6.878) {
                    if (input[1] < 8.361307) {
                        var30 = 197.16328;
                    } else {
                        var30 = -8067.4697;
                    }
                } else {
                    if (input[3] < 21.62854) {
                        var30 = 1220.0192;
                    } else {
                        var30 = -3515.28;
                    }
                }
            } else {
                var30 = 5882.6133;
            }
        }
    } else {
        if (input[0] < 15.245295) {
            if (input[3] < 32.128) {
                if (input[1] < 40.82344) {
                    if (input[1] < 34.761) {
                        var30 = 661.5508;
                    } else {
                        var30 = 8758.399;
                    }
                } else {
                    if (input[3] < 22.746216) {
                        var30 = 2483.9192;
                    } else {
                        var30 = -2758.3955;
                    }
                }
            } else {
                if (input[5] < 5.6158624) {
                    if (input[1] < 58.449) {
                        var30 = 24174.078;
                    } else {
                        var30 = -6872.7583;
                    }
                } else {
                    if (input[4] < 64.54271) {
                        var30 = 8037.0366;
                    } else {
                        var30 = -3420.852;
                    }
                }
            }
        } else {
            if (input[3] < 29.98716) {
                if (input[3] < 28.471) {
                    if (input[2] < 107.78973) {
                        var30 = -11.514241;
                    } else {
                        var30 = -1468.2382;
                    }
                } else {
                    if (input[2] < 222.8815) {
                        var30 = 2039.4669;
                    } else {
                        var30 = -2671.503;
                    }
                }
            } else {
                if (input[1] < 74.361) {
                    if (input[1] < 73.88119) {
                        var30 = -247.7908;
                    } else {
                        var30 = 18327.871;
                    }
                } else {
                    if (input[1] < 84.937) {
                        var30 = -5881.9326;
                    } else {
                        var30 = -873.71783;
                    }
                }
            }
        }
    }
    float var31;
    if (input[1] < 5.729007) {
        if (input[3] < 33.7315) {
            if (input[3] < 31.939474) {
                if (input[3] < 31.094688) {
                    if (input[5] < 7.4391994) {
                        var31 = 538.5459;
                    } else {
                        var31 = 10217.452;
                    }
                } else {
                    if (input[4] < 81.08183) {
                        var31 = 27019.65;
                    } else {
                        var31 = 3728.649;
                    }
                }
            } else {
                if (input[0] < 89.0) {
                    if (input[2] < 139.37782) {
                        var31 = -9964.732;
                    } else {
                        var31 = -838.20825;
                    }
                } else {
                    var31 = 9930.778;
                }
            }
        } else {
            if (input[0] < 39.654034) {
                if (input[2] < 2.1954777) {
                    if (input[0] < 17.0) {
                        var31 = -134.34259;
                    } else {
                        var31 = 686.92035;
                    }
                } else {
                    var31 = 6994.408;
                }
            } else {
                var31 = 33208.395;
            }
        }
    } else {
        if (input[2] < 46.0) {
            if (input[5] < 5.859543) {
                if (input[2] < 26.0) {
                    if (input[3] < 36.64022) {
                        var31 = -765.6096;
                    } else {
                        var31 = 21132.723;
                    }
                } else {
                    if (input[3] < 26.54586) {
                        var31 = 736.39264;
                    } else {
                        var31 = 7857.318;
                    }
                }
            } else {
                if (input[2] < 14.318071) {
                    if (input[4] < 62.15172) {
                        var31 = -656.92395;
                    } else {
                        var31 = 1371.3374;
                    }
                } else {
                    if (input[4] < 51.242733) {
                        var31 = 1540.4567;
                    } else {
                        var31 = -1317.3951;
                    }
                }
            }
        } else {
            if (input[4] < 58.736168) {
                if (input[3] < 28.297476) {
                    if (input[1] < 13.753483) {
                        var31 = -10092.715;
                    } else {
                        var31 = 794.07043;
                    }
                } else {
                    if (input[1] < 79.0) {
                        var31 = -4341.244;
                    } else {
                        var31 = 951.6845;
                    }
                }
            } else {
                if (input[5] < 5.207745) {
                    if (input[1] < 73.0) {
                        var31 = -5830.2354;
                    } else {
                        var31 = 5816.594;
                    }
                } else {
                    if (input[0] < 73.87512) {
                        var31 = 1608.161;
                    } else {
                        var31 = 313.7243;
                    }
                }
            }
        }
    }
    float var32;
    if (input[5] < 4.5161543) {
        if (input[3] < 31.094688) {
            if (input[1] < 80.994) {
                if (input[2] < 26.592365) {
                    if (input[4] < 43.653053) {
                        var32 = -503.02298;
                    } else {
                        var32 = -6332.57;
                    }
                } else {
                    if (input[2] < 216.89438) {
                        var32 = -11327.795;
                    } else {
                        var32 = -2573.8958;
                    }
                }
            } else {
                var32 = 8058.18;
            }
        } else {
            if (input[1] < 48.631) {
                if (input[1] < 27.366035) {
                    var32 = 2080.2188;
                } else {
                    var32 = 17802.389;
                }
            } else {
                var32 = -6297.011;
            }
        }
    } else {
        if (input[3] < 41.382507) {
            if (input[5] < 8.869533) {
                if (input[1] < 5.729007) {
                    if (input[3] < 33.7315) {
                        var32 = 1063.3348;
                    } else {
                        var32 = 15375.649;
                    }
                } else {
                    if (input[0] < 115.34102) {
                        var32 = -124.36753;
                    } else {
                        var32 = 483.2553;
                    }
                }
            } else {
                if (input[2] < 31.056194) {
                    if (input[0] < 40.0) {
                        var32 = -3904.8665;
                    } else {
                        var32 = -8349.368;
                    }
                } else {
                    if (input[0] < 1.1725864) {
                        var32 = -2211.8467;
                    } else {
                        var32 = 6525.145;
                    }
                }
            }
        } else {
            if (input[4] < 89.236465) {
                if (input[1] < 70.363686) {
                    if (input[4] < 88.30406) {
                        var32 = 14781.706;
                    } else {
                        var32 = 4994.877;
                    }
                } else {
                    var32 = -1408.4204;
                }
            } else {
                if (input[2] < 64.48997) {
                    if (input[0] < 57.0) {
                        var32 = 1812.997;
                    } else {
                        var32 = -1530.2875;
                    }
                } else {
                    if (input[2] < 73.0) {
                        var32 = 12168.451;
                    } else {
                        var32 = 854.761;
                    }
                }
            }
        }
    }
    float var33;
    if (input[4] < 43.653053) {
        if (input[3] < 26.286404) {
            if (input[1] < 43.0) {
                if (input[4] < 41.51) {
                    var33 = 19050.268;
                } else {
                    if (input[1] < 30.79545) {
                        var33 = -3455.7227;
                    } else {
                        var33 = 1022.31213;
                    }
                }
            } else {
                if (input[4] < 36.52781) {
                    if (input[2] < 25.0) {
                        var33 = -297.82764;
                    } else {
                        var33 = -1487.6027;
                    }
                } else {
                    var33 = -4489.93;
                }
            }
        } else {
            if (input[3] < 29.417381) {
                if (input[0] < 1.1725864) {
                    if (input[1] < 32.156) {
                        var33 = 11654.541;
                    } else {
                        var33 = -5740.4277;
                    }
                } else {
                    if (input[1] < 42.585133) {
                        var33 = -10239.181;
                    } else {
                        var33 = -4662.095;
                    }
                }
            } else {
                if (input[2] < 51.675453) {
                    if (input[5] < 6.354192) {
                        var33 = -6878.09;
                    } else {
                        var33 = -1434.822;
                    }
                } else {
                    if (input[2] < 62.498127) {
                        var33 = 13657.134;
                    } else {
                        var33 = -1617.8772;
                    }
                }
            }
        }
    } else {
        if (input[4] < 50.8) {
            if (input[0] < 34.851887) {
                if (input[3] < 30.583355) {
                    if (input[5] < 5.731) {
                        var33 = 8146.4155;
                    } else {
                        var33 = -1961.986;
                    }
                } else {
                    if (input[5] < 7.081) {
                        var33 = 17927.88;
                    } else {
                        var33 = -7910.785;
                    }
                }
            } else {
                if (input[5] < 7.5) {
                    if (input[2] < 130.0) {
                        var33 = -309.67767;
                    } else {
                        var33 = -8332.053;
                    }
                } else {
                    if (input[0] < 132.15015) {
                        var33 = 12893.288;
                    } else {
                        var33 = -12132.002;
                    }
                }
            }
        } else {
            if (input[2] < 46.0) {
                if (input[2] < 14.318071) {
                    if (input[1] < 64.764984) {
                        var33 = 45.00815;
                    } else {
                        var33 = 3462.7644;
                    }
                } else {
                    if (input[1] < 94.0) {
                        var33 = -839.1259;
                    } else {
                        var33 = 17010.557;
                    }
                }
            } else {
                if (input[4] < 58.736168) {
                    if (input[3] < 28.297476) {
                        var33 = 592.8877;
                    } else {
                        var33 = -2716.2021;
                    }
                } else {
                    if (input[5] < 6.182233) {
                        var33 = -125.26471;
                    } else {
                        var33 = 1052.3333;
                    }
                }
            }
        }
    }
    float var34;
    if (input[5] < 4.5161543) {
        if (input[3] < 31.094688) {
            if (input[1] < 80.994) {
                if (input[4] < 65.29959) {
                    if (input[0] < 49.03933) {
                        var34 = -6779.1626;
                    } else {
                        var34 = -2422.1213;
                    }
                } else {
                    var34 = -13223.646;
                }
            } else {
                var34 = 7264.886;
            }
        } else {
            if (input[1] < 48.631) {
                if (input[1] < 27.366035) {
                    var34 = 579.61176;
                } else {
                    var34 = 15170.406;
                }
            } else {
                var34 = -7169.3257;
            }
        }
    } else {
        if (input[4] < 94.267654) {
            if (input[2] < 265.0) {
                if (input[0] < 115.34102) {
                    if (input[5] < 5.859543) {
                        var34 = 779.1984;
                    } else {
                        var34 = -331.12772;
                    }
                } else {
                    if (input[2] < 167.9841) {
                        var34 = 50.32747;
                    } else {
                        var34 = 3761.0322;
                    }
                }
            } else {
                if (input[3] < 27.955414) {
                    if (input[5] < 7.038153) {
                        var34 = -1184.8098;
                    } else {
                        var34 = 2956.8174;
                    }
                } else {
                    if (input[5] < 5.663428) {
                        var34 = 1431.653;
                    } else {
                        var34 = -2319.4514;
                    }
                }
            }
        } else {
            if (input[2] < 36.36481) {
                if (input[1] < 25.177479) {
                    if (input[0] < 59.170143) {
                        var34 = 1764.4407;
                    } else {
                        var34 = -4049.3591;
                    }
                } else {
                    if (input[0] < 56.0) {
                        var34 = 3455.154;
                    } else {
                        var34 = 9685.581;
                    }
                }
            } else {
                if (input[0] < 31.742155) {
                    if (input[2] < 194.99553) {
                        var34 = 3148.9287;
                    } else {
                        var34 = -928.94855;
                    }
                } else {
                    if (input[5] < 5.912248) {
                        var34 = -6455.2476;
                    } else {
                        var34 = -240.54118;
                    }
                }
            }
        }
    }
    float var35;
    if (input[2] < 197.0) {
        if (input[2] < 167.9841) {
            if (input[0] < 148.22476) {
                if (input[1] < 86.0) {
                    if (input[2] < 163.0) {
                        var35 = 29.811085;
                    } else {
                        var35 = -5482.024;
                    }
                } else {
                    if (input[4] < 52.008) {
                        var35 = -4687.542;
                    } else {
                        var35 = 4538.735;
                    }
                }
            } else {
                if (input[1] < 80.13198) {
                    if (input[2] < 140.32973) {
                        var35 = -433.36365;
                    } else {
                        var35 = -10866.98;
                    }
                } else {
                    if (input[1] < 91.0) {
                        var35 = -13671.605;
                    } else {
                        var35 = 2942.2383;
                    }
                }
            }
        } else {
            if (input[3] < 28.782078) {
                if (input[3] < 28.730688) {
                    if (input[2] < 171.74876) {
                        var35 = 12513.442;
                    } else {
                        var35 = 327.22278;
                    }
                } else {
                    if (input[5] < 5.800449) {
                        var35 = 5688.398;
                    } else {
                        var35 = 17900.076;
                    }
                }
            } else {
                if (input[2] < 176.10364) {
                    if (input[1] < 80.994) {
                        var35 = -14916.354;
                    } else {
                        var35 = 8565.2;
                    }
                } else {
                    if (input[4] < 62.93049) {
                        var35 = -4476.682;
                    } else {
                        var35 = 6037.7896;
                    }
                }
            }
        }
    } else {
        if (input[5] < 5.279389) {
            if (input[2] < 222.8815) {
                if (input[0] < 96.0) {
                    if (input[0] < 1.1725864) {
                        var35 = 3295.636;
                    } else {
                        var35 = -4456.463;
                    }
                } else {
                    if (input[5] < 4.6993885) {
                        var35 = -5292.4644;
                    } else {
                        var35 = -17740.844;
                    }
                }
            } else {
                if (input[1] < 33.02747) {
                    if (input[0] < 84.0) {
                        var35 = -399.73477;
                    } else {
                        var35 = -4534.958;
                    }
                } else {
                    if (input[0] < 114.82001) {
                        var35 = -2053.1199;
                    } else {
                        var35 = 3787.795;
                    }
                }
            }
        } else {
            if (input[1] < 70.363686) {
                if (input[2] < 198.60103) {
                    if (input[4] < 65.510216) {
                        var35 = -8724.202;
                    } else {
                        var35 = 6018.1606;
                    }
                } else {
                    if (input[2] < 222.8815) {
                        var35 = 7807.76;
                    } else {
                        var35 = 513.15674;
                    }
                }
            } else {
                if (input[3] < 30.325754) {
                    if (input[4] < 58.060223) {
                        var35 = 4147.406;
                    } else {
                        var35 = -1396.053;
                    }
                } else {
                    if (input[1] < 86.0) {
                        var35 = -11721.432;
                    } else {
                        var35 = -2547.9717;
                    }
                }
            }
        }
    }
    float var36;
    if (input[0] < 191.0) {
        if (input[1] < 19.51048) {
            if (input[1] < 15.899695) {
                if (input[4] < 53.688843) {
                    if (input[5] < 5.322044) {
                        var36 = 15207.361;
                    } else {
                        var36 = -5176.929;
                    }
                } else {
                    if (input[4] < 53.937) {
                        var36 = 31077.572;
                    } else {
                        var36 = 345.01328;
                    }
                }
            } else {
                if (input[4] < 54.712) {
                    if (input[3] < 22.906) {
                        var36 = -2171.0398;
                    } else {
                        var36 = 15625.575;
                    }
                } else {
                    if (input[5] < 6.138959) {
                        var36 = -2066.4595;
                    } else {
                        var36 = 2178.133;
                    }
                }
            }
        } else {
            if (input[1] < 56.432) {
                if (input[4] < 50.356) {
                    if (input[2] < 41.304405) {
                        var36 = 3848.022;
                    } else {
                        var36 = -2571.115;
                    }
                } else {
                    if (input[2] < 181.15967) {
                        var36 = -535.5542;
                    } else {
                        var36 = 3260.6328;
                    }
                }
            } else {
                if (input[0] < 42.0) {
                    if (input[3] < 26.97982) {
                        var36 = 261.27133;
                    } else {
                        var36 = -2802.172;
                    }
                } else {
                    if (input[0] < 82.484764) {
                        var36 = 2604.6592;
                    } else {
                        var36 = -46.720505;
                    }
                }
            }
        }
    } else {
        if (input[5] < 6.679226) {
            if (input[5] < 5.833302) {
                if (input[2] < 222.8815) {
                    if (input[1] < 49.280045) {
                        var36 = -12606.579;
                    } else {
                        var36 = -1620.1255;
                    }
                } else {
                    if (input[2] < 285.15762) {
                        var36 = 5189.995;
                    } else {
                        var36 = -2949.023;
                    }
                }
            } else {
                if (input[1] < 76.129616) {
                    if (input[3] < 27.690199) {
                        var36 = -2667.2659;
                    } else {
                        var36 = 14849.453;
                    }
                } else {
                    if (input[2] < 332.74554) {
                        var36 = -3964.9866;
                    } else {
                        var36 = -956.093;
                    }
                }
            }
        } else {
            if (input[2] < 222.8815) {
                var36 = -24178.986;
            } else {
                if (input[0] < 257.0) {
                    if (input[5] < 6.83068) {
                        var36 = -5631.025;
                    } else {
                        var36 = -2066.0146;
                    }
                } else {
                    var36 = -9353.593;
                }
            }
        }
    }
    float var37;
    if (input[4] < 45.26633) {
        if (input[0] < 152.0) {
            if (input[5] < 5.207745) {
                if (input[3] < 25.484293) {
                    if (input[2] < 41.304405) {
                        var37 = -2055.3345;
                    } else {
                        var37 = 5356.983;
                    }
                } else {
                    if (input[0] < 13.0) {
                        var37 = -9358.93;
                    } else {
                        var37 = -4520.525;
                    }
                }
            } else {
                if (input[3] < 29.046381) {
                    if (input[3] < 27.561304) {
                        var37 = -714.8927;
                    } else {
                        var37 = -6892.1143;
                    }
                } else {
                    if (input[4] < 43.653053) {
                        var37 = -848.46906;
                    } else {
                        var37 = 5916.442;
                    }
                }
            }
        } else {
            if (input[2] < 1.0) {
                var37 = -72.5168;
            } else {
                var37 = -14522.862;
            }
        }
    } else {
        if (input[4] < 46.174072) {
            if (input[1] < 47.556) {
                if (input[5] < 6.9651566) {
                    if (input[2] < 37.0) {
                        var37 = 23841.7;
                    } else {
                        var37 = 435.96097;
                    }
                } else {
                    if (input[0] < 143.0) {
                        var37 = -11703.941;
                    } else {
                        var37 = 10173.068;
                    }
                }
            } else {
                if (input[2] < 27.126823) {
                    if (input[0] < 65.0) {
                        var37 = -7729.2144;
                    } else {
                        var37 = -17503.041;
                    }
                } else {
                    if (input[0] < 45.45008) {
                        var37 = -2503.9136;
                    } else {
                        var37 = 22091.305;
                    }
                }
            }
        } else {
            if (input[0] < 1.1725864) {
                if (input[4] < 52.94) {
                    if (input[3] < 28.947046) {
                        var37 = 3985.506;
                    } else {
                        var37 = 24285.703;
                    }
                } else {
                    if (input[3] < 34.1759) {
                        var37 = -363.16342;
                    } else {
                        var37 = 13671.066;
                    }
                }
            } else {
                if (input[1] < 6.329044) {
                    if (input[3] < 33.04688) {
                        var37 = 1121.931;
                    } else {
                        var37 = 12946.022;
                    }
                } else {
                    if (input[3] < 29.98716) {
                        var37 = 98.86705;
                    } else {
                        var37 = -455.2779;
                    }
                }
            }
        }
    }
    float var38;
    if (input[2] < 197.0) {
        if (input[2] < 167.9841) {
            if (input[3] < 14.039053) {
                if (input[4] < 68.74849) {
                    if (input[5] < 5.912248) {
                        var38 = -4559.0913;
                    } else {
                        var38 = 1509.7643;
                    }
                } else {
                    if (input[4] < 88.72857) {
                        var38 = 14395.983;
                    } else {
                        var38 = 2582.172;
                    }
                }
            } else {
                if (input[0] < 148.22476) {
                    if (input[5] < 5.859543) {
                        var38 = 799.2983;
                    } else {
                        var38 = -132.17792;
                    }
                } else {
                    if (input[5] < 5.944756) {
                        var38 = -5815.4985;
                    } else {
                        var38 = -136.98499;
                    }
                }
            }
        } else {
            if (input[4] < 60.50321) {
                if (input[1] < 50.704) {
                    if (input[4] < 58.426605) {
                        var38 = -5239.7896;
                    } else {
                        var38 = 4752.8374;
                    }
                } else {
                    if (input[3] < 26.286404) {
                        var38 = -947.1008;
                    } else {
                        var38 = 12040.656;
                    }
                }
            } else {
                if (input[3] < 27.141937) {
                    if (input[2] < 171.74876) {
                        var38 = 18828.775;
                    } else {
                        var38 = -403.00116;
                    }
                } else {
                    if (input[5] < 6.205238) {
                        var38 = -8803.073;
                    } else {
                        var38 = 1694.9614;
                    }
                }
            }
        }
    } else {
        if (input[5] < 5.9672027) {
            if (input[1] < 35.509106) {
                if (input[5] < 5.6) {
                    if (input[5] < 5.585289) {
                        var38 = -5426.959;
                    } else {
                        var38 = 5931.8228;
                    }
                } else {
                    if (input[0] < 171.0) {
                        var38 = -16339.537;
                    } else {
                        var38 = -2843.856;
                    }
                }
            } else {
                if (input[0] < 132.15015) {
                    if (input[0] < 111.0) {
                        var38 = -1295.7267;
                    } else {
                        var38 = -7569.0425;
                    }
                } else {
                    if (input[5] < 5.279389) {
                        var38 = -5269.013;
                    } else {
                        var38 = 2515.8364;
                    }
                }
            }
        } else {
            if (input[1] < 49.280045) {
                if (input[1] < 29.27178) {
                    if (input[5] < 6.046462) {
                        var38 = 9447.996;
                    } else {
                        var38 = -4182.842;
                    }
                } else {
                    if (input[2] < 252.28195) {
                        var38 = 15186.921;
                    } else {
                        var38 = -3700.2266;
                    }
                }
            } else {
                if (input[3] < 31.767136) {
                    if (input[2] < 232.28062) {
                        var38 = 1052.2429;
                    } else {
                        var38 = -1401.4493;
                    }
                } else {
                    if (input[1] < 86.0) {
                        var38 = -14934.933;
                    } else {
                        var38 = -1423.9662;
                    }
                }
            }
        }
    }
    float var39;
    if (input[5] < 4.5161543) {
        if (input[3] < 31.094688) {
            if (input[1] < 80.994) {
                if (input[4] < 65.29959) {
                    if (input[0] < 49.03933) {
                        var39 = -5778.3594;
                    } else {
                        var39 = -1298.8945;
                    }
                } else {
                    var39 = -10737.541;
                }
            } else {
                var39 = 4760.277;
            }
        } else {
            if (input[1] < 48.631) {
                if (input[1] < 27.366035) {
                    var39 = -1602.7736;
                } else {
                    var39 = 13149.705;
                }
            } else {
                var39 = -6449.5005;
            }
        }
    } else {
        if (input[3] < 41.382507) {
            if (input[4] < 45.26633) {
                if (input[0] < 152.0) {
                    if (input[5] < 5.207745) {
                        var39 = -4234.065;
                    } else {
                        var39 = -605.19574;
                    }
                } else {
                    if (input[2] < 1.0) {
                        var39 = -56.8043;
                    } else {
                        var39 = -12433.209;
                    }
                }
            } else {
                if (input[4] < 46.174072) {
                    if (input[1] < 47.556) {
                        var39 = 13015.954;
                    } else {
                        var39 = -2004.1886;
                    }
                } else {
                    if (input[0] < 15.245295) {
                        var39 = 781.70703;
                    } else {
                        var39 = -51.518223;
                    }
                }
            }
        } else {
            if (input[4] < 89.236465) {
                if (input[2] < 63.64638) {
                    var39 = 12183.527;
                } else {
                    if (input[3] < 48.37565) {
                        var39 = -532.8328;
                    } else {
                        var39 = 5212.5215;
                    }
                }
            } else {
                if (input[0] < 25.973791) {
                    var39 = 12174.314;
                } else {
                    if (input[2] < 55.530315) {
                        var39 = -678.6994;
                    } else {
                        var39 = 2572.1602;
                    }
                }
            }
        }
    }
    float var40;
    if (input[4] < 91.70293) {
        if (input[3] < 41.382507) {
            if (input[0] < 115.34102) {
                if (input[2] < 194.99553) {
                    if (input[1] < 86.0) {
                        var40 = -184.5961;
                    } else {
                        var40 = 3493.272;
                    }
                } else {
                    if (input[4] < 65.76002) {
                        var40 = -5162.917;
                    } else {
                        var40 = -387.4164;
                    }
                }
            } else {
                if (input[5] < 6.094) {
                    if (input[0] < 117.442154) {
                        var40 = 5649.5356;
                    } else {
                        var40 = -1656.9662;
                    }
                } else {
                    if (input[5] < 6.191) {
                        var40 = 7591.9434;
                    } else {
                        var40 = 719.20416;
                    }
                }
            }
        } else {
            if (input[4] < 88.30406) {
                if (input[1] < 70.363686) {
                    var40 = 11554.052;
                } else {
                    var40 = -860.1668;
                }
            } else {
                if (input[0] < 43.347652) {
                    var40 = 4194.097;
                } else {
                    if (input[0] < 44.382317) {
                        var40 = -106.762505;
                    } else {
                        var40 = 140.84297;
                    }
                }
            }
        }
    } else {
        if (input[2] < 34.69221) {
            if (input[1] < 35.509106) {
                if (input[5] < 6.381084) {
                    if (input[0] < 55.0) {
                        var40 = 1482.2483;
                    } else {
                        var40 = 7454.957;
                    }
                } else {
                    if (input[0] < 58.46179) {
                        var40 = 834.70544;
                    } else {
                        var40 = -6283.748;
                    }
                }
            } else {
                if (input[5] < 5.403444) {
                    var40 = -9683.473;
                } else {
                    if (input[0] < 36.0) {
                        var40 = 10162.411;
                    } else {
                        var40 = 3555.7883;
                    }
                }
            }
        } else {
            if (input[5] < 7.5935574) {
                if (input[1] < 39.235302) {
                    if (input[1] < 37.733498) {
                        var40 = -626.40656;
                    } else {
                        var40 = -18901.707;
                    }
                } else {
                    if (input[1] < 58.033756) {
                        var40 = 6272.1875;
                    } else {
                        var40 = 209.32835;
                    }
                }
            } else {
                if (input[0] < 13.997322) {
                    var40 = -2245.1484;
                } else {
                    var40 = -28245.314;
                }
            }
        }
    }
    float var41;
    if (input[3] < 28.471) {
        if (input[0] < 82.484764) {
            if (input[3] < 27.824) {
                if (input[5] < 4.6993885) {
                    if (input[2] < 47.609932) {
                        var41 = -6857.79;
                    } else {
                        var41 = 4323.2314;
                    }
                } else {
                    if (input[1] < 34.761) {
                        var41 = -325.1083;
                    } else {
                        var41 = 670.67664;
                    }
                }
            } else {
                if (input[1] < 60.40199) {
                    if (input[5] < 6.4605427) {
                        var41 = -510.40225;
                    } else {
                        var41 = -6467.541;
                    }
                } else {
                    if (input[1] < 76.805) {
                        var41 = 11635.745;
                    } else {
                        var41 = -5304.0425;
                    }
                }
            }
        } else {
            if (input[5] < 6.364) {
                if (input[4] < 64.3835) {
                    if (input[1] < 71.86359) {
                        var41 = 163.39003;
                    } else {
                        var41 = -6320.957;
                    }
                } else {
                    if (input[1] < 51.183098) {
                        var41 = -876.44354;
                    } else {
                        var41 = 3540.0378;
                    }
                }
            } else {
                if (input[4] < 63.314106) {
                    if (input[1] < 20.432287) {
                        var41 = 5686.183;
                    } else {
                        var41 = -939.99274;
                    }
                } else {
                    if (input[4] < 80.18547) {
                        var41 = -4101.9395;
                    } else {
                        var41 = -793.12225;
                    }
                }
            }
        }
    } else {
        if (input[3] < 28.947046) {
            if (input[1] < 73.0) {
                if (input[1] < 35.0) {
                    if (input[5] < 5.731) {
                        var41 = -4884.25;
                    } else {
                        var41 = 5292.865;
                    }
                } else {
                    if (input[2] < 163.0) {
                        var41 = -5389.1646;
                    } else {
                        var41 = 3477.704;
                    }
                }
            } else {
                if (input[2] < 216.89438) {
                    if (input[2] < 125.0) {
                        var41 = 1496.481;
                    } else {
                        var41 = 13994.398;
                    }
                } else {
                    if (input[1] < 76.129616) {
                        var41 = 2764.05;
                    } else {
                        var41 = -2687.617;
                    }
                }
            }
        } else {
            if (input[1] < 66.986) {
                if (input[4] < 50.356) {
                    if (input[0] < 34.052402) {
                        var41 = 7971.943;
                    } else {
                        var41 = -361.4659;
                    }
                } else {
                    if (input[4] < 66.61547) {
                        var41 = -524.0564;
                    } else {
                        var41 = 1285.396;
                    }
                }
            } else {
                if (input[5] < 6.066255) {
                    if (input[2] < 50.196278) {
                        var41 = -11934.094;
                    } else {
                        var41 = -1772.2402;
                    }
                } else {
                    if (input[5] < 6.191) {
                        var41 = 7519.6733;
                    } else {
                        var41 = -1036.8134;
                    }
                }
            }
        }
    }
    float var42;
    if (input[4] < 43.653053) {
        if (input[3] < 26.286404) {
            if (input[1] < 43.0) {
                if (input[4] < 41.51) {
                    var42 = 16515.549;
                } else {
                    if (input[1] < 30.79545) {
                        var42 = -2665.1313;
                    } else {
                        var42 = 826.7836;
                    }
                }
            } else {
                if (input[4] < 36.52781) {
                    if (input[2] < 10.0) {
                        var42 = -1882.0726;
                    } else {
                        var42 = -461.97842;
                    }
                } else {
                    var42 = -3808.8901;
                }
            }
        } else {
            if (input[0] < 99.58935) {
                if (input[2] < 42.788017) {
                    if (input[1] < 23.31191) {
                        var42 = -8095.4785;
                    } else {
                        var42 = -2711.8574;
                    }
                } else {
                    if (input[2] < 62.498127) {
                        var42 = 8744.118;
                    } else {
                        var42 = -2998.413;
                    }
                }
            } else {
                if (input[1] < 91.0) {
                    if (input[5] < 6.8539267) {
                        var42 = -8756.999;
                    } else {
                        var42 = 297.70312;
                    }
                } else {
                    var42 = 684.79926;
                }
            }
        }
    } else {
        if (input[4] < 50.8) {
            if (input[2] < 49.88706) {
                if (input[2] < 24.781227) {
                    if (input[2] < 16.438295) {
                        var42 = 599.6319;
                    } else {
                        var42 = -7362.471;
                    }
                } else {
                    if (input[0] < 77.16157) {
                        var42 = 12814.142;
                    } else {
                        var42 = -3351.616;
                    }
                }
            } else {
                if (input[5] < 6.9960284) {
                    if (input[1] < 32.60599) {
                        var42 = -9606.573;
                    } else {
                        var42 = -1279.3503;
                    }
                } else {
                    if (input[2] < 102.0) {
                        var42 = -2795.0073;
                    } else {
                        var42 = 7612.013;
                    }
                }
            }
        } else {
            if (input[2] < 40.27596) {
                if (input[4] < 61.187885) {
                    if (input[1] < 62.443718) {
                        var42 = -1296.3855;
                    } else {
                        var42 = 2683.97;
                    }
                } else {
                    if (input[0] < 108.686226) {
                        var42 = -3.8210728;
                    } else {
                        var42 = 2614.207;
                    }
                }
            } else {
                if (input[5] < 5.279389) {
                    if (input[4] < 53.331158) {
                        var42 = 8798.866;
                    } else {
                        var42 = -2522.2314;
                    }
                } else {
                    if (input[4] < 52.94) {
                        var42 = -3011.094;
                    } else {
                        var42 = 395.63358;
                    }
                }
            }
        }
    }
    float var43;
    if (input[0] < 191.0) {
        if (input[0] < 126.0) {
            if (input[5] < 5.5697627) {
                if (input[2] < 24.781227) {
                    if (input[1] < 40.82344) {
                        var43 = 2390.2146;
                    } else {
                        var43 = -3625.1196;
                    }
                } else {
                    if (input[4] < 54.928) {
                        var43 = 7265.684;
                    } else {
                        var43 = 573.35846;
                    }
                }
            } else {
                if (input[0] < 82.0) {
                    if (input[1] < 50.348312) {
                        var43 = -347.4245;
                    } else {
                        var43 = 795.9771;
                    }
                } else {
                    if (input[2] < 116.0) {
                        var43 = -304.02982;
                    } else {
                        var43 = -2771.5193;
                    }
                }
            }
        } else {
            if (input[0] < 133.58269) {
                if (input[3] < 30.583355) {
                    if (input[3] < 29.497864) {
                        var43 = 2845.4023;
                    } else {
                        var43 = -4818.7056;
                    }
                } else {
                    if (input[2] < 51.0) {
                        var43 = 21207.1;
                    } else {
                        var43 = 627.1587;
                    }
                }
            } else {
                if (input[2] < 85.0) {
                    if (input[1] < 80.13198) {
                        var43 = -1044.2245;
                    } else {
                        var43 = -10828.662;
                    }
                } else {
                    if (input[4] < 78.459595) {
                        var43 = 1416.6216;
                    } else {
                        var43 = -13158.063;
                    }
                }
            }
        }
    } else {
        if (input[5] < 6.679226) {
            if (input[5] < 5.833302) {
                if (input[2] < 222.8815) {
                    if (input[1] < 49.280045) {
                        var43 = -10825.251;
                    } else {
                        var43 = -764.81836;
                    }
                } else {
                    if (input[2] < 285.15762) {
                        var43 = 4586.5493;
                    } else {
                        var43 = -2254.5156;
                    }
                }
            } else {
                if (input[1] < 76.129616) {
                    if (input[3] < 27.690199) {
                        var43 = -2525.6177;
                    } else {
                        var43 = 13351.048;
                    }
                } else {
                    if (input[5] < 6.481) {
                        var43 = -3632.198;
                    } else {
                        var43 = -1149.2961;
                    }
                }
            }
        } else {
            if (input[2] < 222.8815) {
                var43 = -21639.639;
            } else {
                if (input[2] < 252.28195) {
                    if (input[5] < 7.4391994) {
                        var43 = -9312.213;
                    } else {
                        var43 = -1966.9231;
                    }
                } else {
                    if (input[3] < 28.782078) {
                        var43 = -3828.3972;
                    } else {
                        var43 = 3234.3687;
                    }
                }
            }
        }
    }
    float var44;
    if (input[2] < 194.99553) {
        if (input[2] < 181.15967) {
            if (input[0] < 148.22476) {
                if (input[0] < 126.0) {
                    if (input[5] < 5.859543) {
                        var44 = 699.269;
                    } else {
                        var44 = -154.0604;
                    }
                } else {
                    if (input[0] < 133.58269) {
                        var44 = 3006.2212;
                    } else {
                        var44 = -189.64713;
                    }
                }
            } else {
                if (input[1] < 81.823) {
                    if (input[2] < 112.69621) {
                        var44 = 170.11578;
                    } else {
                        var44 = -4434.3457;
                    }
                } else {
                    if (input[3] < 28.186907) {
                        var44 = -15899.321;
                    } else {
                        var44 = -5455.6973;
                    }
                }
            }
        } else {
            if (input[4] < 60.43509) {
                if (input[4] < 57.23537) {
                    if (input[1] < 71.86359) {
                        var44 = -4700.1387;
                    } else {
                        var44 = 7980.85;
                    }
                } else {
                    if (input[3] < 26.494326) {
                        var44 = -10282.109;
                    } else {
                        var44 = 12241.086;
                    }
                }
            } else {
                if (input[5] < 6.4423933) {
                    if (input[4] < 61.187885) {
                        var44 = -17770.059;
                    } else {
                        var44 = -1731.3756;
                    }
                } else {
                    if (input[0] < 111.0) {
                        var44 = 1868.1947;
                    } else {
                        var44 = 21753.867;
                    }
                }
            }
        }
    } else {
        if (input[3] < 32.128) {
            if (input[3] < 19.504145) {
                if (input[1] < 60.40199) {
                    var44 = -9930.65;
                } else {
                    if (input[5] < 5.8470073) {
                        var44 = -5233.782;
                    } else {
                        var44 = -2331.0322;
                    }
                }
            } else {
                if (input[5] < 5.9672027) {
                    if (input[1] < 35.509106) {
                        var44 = -4504.2153;
                    } else {
                        var44 = -957.177;
                    }
                } else {
                    if (input[1] < 49.280045) {
                        var44 = 6380.4243;
                    } else {
                        var44 = -312.7141;
                    }
                }
            }
        } else {
            if (input[5] < 5.5225325) {
                if (input[0] < 65.0) {
                    var44 = 14809.515;
                } else {
                    if (input[0] < 87.76143) {
                        var44 = -237.99962;
                    } else {
                        var44 = 3291.6118;
                    }
                }
            } else {
                if (input[0] < 40.908596) {
                    if (input[1] < 7.0) {
                        var44 = 6129.4556;
                    } else {
                        var44 = -2876.0608;
                    }
                } else {
                    if (input[2] < 222.8815) {
                        var44 = -18693.05;
                    } else {
                        var44 = -2283.4175;
                    }
                }
            }
        }
    }
    float var45;
    if (input[4] < 47.599) {
        if (input[1] < 40.324883) {
            if (input[5] < 6.5) {
                if (input[0] < 38.35763) {
                    if (input[3] < 27.034096) {
                        var45 = -5052.3516;
                    } else {
                        var45 = 17929.879;
                    }
                } else {
                    if (input[2] < 29.0) {
                        var45 = -9627.474;
                    } else {
                        var45 = 3490.7961;
                    }
                }
            } else {
                if (input[4] < 46.97937) {
                    if (input[2] < 15.069769) {
                        var45 = -6320.0195;
                    } else {
                        var45 = 2650.3052;
                    }
                } else {
                    var45 = -13579.411;
                }
            }
        } else {
            if (input[4] < 46.174072) {
                if (input[0] < 60.512794) {
                    if (input[3] < 25.067081) {
                        var45 = -754.7407;
                    } else {
                        var45 = -3992.0308;
                    }
                } else {
                    if (input[0] < 76.0) {
                        var45 = 17176.559;
                    } else {
                        var45 = -1706.5206;
                    }
                }
            } else {
                if (input[0] < 65.0) {
                    if (input[5] < 6.046462) {
                        var45 = -16565.299;
                    } else {
                        var45 = -7944.139;
                    }
                } else {
                    if (input[2] < 61.64904) {
                        var45 = 7228.1196;
                    } else {
                        var45 = -5702.1504;
                    }
                }
            }
        }
    } else {
        if (input[2] < 14.318071) {
            if (input[1] < 35.007843) {
                if (input[5] < 4.992127) {
                    if (input[5] < 4.5161543) {
                        var45 = 741.2604;
                    } else {
                        var45 = 26732.184;
                    }
                } else {
                    if (input[5] < 5.207745) {
                        var45 = -26687.914;
                    } else {
                        var45 = -372.27975;
                    }
                }
            } else {
                if (input[4] < 78.0866) {
                    if (input[4] < 77.621) {
                        var45 = 1655.2089;
                    } else {
                        var45 = 18683.98;
                    }
                } else {
                    if (input[3] < 21.349854) {
                        var45 = 14720.558;
                    } else {
                        var45 = -4181.093;
                    }
                }
            }
        } else {
            if (input[1] < 21.487978) {
                if (input[0] < 36.555195) {
                    if (input[5] < 5.6444864) {
                        var45 = 6464.101;
                    } else {
                        var45 = 1150.5721;
                    }
                } else {
                    if (input[4] < 79.800606) {
                        var45 = 1321.9016;
                    } else {
                        var45 = -1918.1685;
                    }
                }
            } else {
                if (input[2] < 39.0) {
                    if (input[4] < 50.356) {
                        var45 = 5478.6055;
                    } else {
                        var45 = -1031.8359;
                    }
                } else {
                    if (input[0] < 73.0) {
                        var45 = 712.1109;
                    } else {
                        var45 = -412.7368;
                    }
                }
            }
        }
    }
    float var46;
    if (input[5] < 6.007) {
        if (input[0] < 34.851887) {
            if (input[1] < 40.82344) {
                if (input[4] < 53.331158) {
                    if (input[2] < 34.69221) {
                        var46 = 13898.398;
                    } else {
                        var46 = 2442.1243;
                    }
                } else {
                    if (input[3] < 32.128) {
                        var46 = 1413.4653;
                    } else {
                        var46 = 20077.943;
                    }
                }
            } else {
                if (input[3] < 26.091282) {
                    if (input[3] < 26.023048) {
                        var46 = -337.30164;
                    } else {
                        var46 = 18023.697;
                    }
                } else {
                    if (input[3] < 33.271) {
                        var46 = -7014.7866;
                    } else {
                        var46 = 4554.3057;
                    }
                }
            }
        } else {
            if (input[4] < 67.18) {
                if (input[1] < 80.994) {
                    if (input[1] < 39.915737) {
                        var46 = -2344.7136;
                    } else {
                        var46 = -995.5308;
                    }
                } else {
                    if (input[3] < 28.76) {
                        var46 = -5230.7695;
                    } else {
                        var46 = 5475.0835;
                    }
                }
            } else {
                if (input[0] < 89.0) {
                    if (input[3] < 32.26) {
                        var46 = -431.4652;
                    } else {
                        var46 = -11873.815;
                    }
                } else {
                    if (input[4] < 72.646) {
                        var46 = 9792.5625;
                    } else {
                        var46 = 1666.9575;
                    }
                }
            }
        }
    } else {
        if (input[0] < 126.0) {
            if (input[3] < 20.619783) {
                if (input[4] < 76.173) {
                    if (input[4] < 66.393) {
                        var46 = 936.98895;
                    } else {
                        var46 = -4974.52;
                    }
                } else {
                    if (input[0] < 98.72169) {
                        var46 = 3108.9666;
                    } else {
                        var46 = 29836.201;
                    }
                }
            } else {
                if (input[1] < 50.0) {
                    if (input[5] < 6.055155) {
                        var46 = 2636.7173;
                    } else {
                        var46 = -662.79456;
                    }
                } else {
                    if (input[0] < 82.0) {
                        var46 = 1109.4962;
                    } else {
                        var46 = -851.4046;
                    }
                }
            }
        } else {
            if (input[1] < 80.13198) {
                if (input[5] < 7.3965125) {
                    if (input[2] < 176.10364) {
                        var46 = 1347.306;
                    } else {
                        var46 = 5036.6963;
                    }
                } else {
                    if (input[2] < 20.337639) {
                        var46 = -11063.049;
                    } else {
                        var46 = -621.8393;
                    }
                }
            } else {
                if (input[3] < 32.718235) {
                    if (input[2] < 75.25433) {
                        var46 = -10963.919;
                    } else {
                        var46 = -1571.7617;
                    }
                } else {
                    if (input[0] < 148.22476) {
                        var46 = 12778.244;
                    } else {
                        var46 = -5611.59;
                    }
                }
            }
        }
    }
    float var47;
    if (input[2] < 194.99553) {
        if (input[2] < 181.15967) {
            if (input[0] < 140.0) {
                if (input[0] < 126.0) {
                    if (input[3] < 14.039053) {
                        var47 = 2781.4692;
                    } else {
                        var47 = -7.3975105;
                    }
                } else {
                    if (input[3] < 27.034096) {
                        var47 = -628.2279;
                    } else {
                        var47 = 2835.5361;
                    }
                }
            } else {
                if (input[5] < 5.944756) {
                    if (input[1] < 10.059196) {
                        var47 = 12097.815;
                    } else {
                        var47 = -4673.2793;
                    }
                } else {
                    if (input[5] < 7.0933285) {
                        var47 = 583.93066;
                    } else {
                        var47 = -3689.2437;
                    }
                }
            }
        } else {
            if (input[4] < 60.43509) {
                if (input[4] < 55.887) {
                    if (input[2] < 191.0) {
                        var47 = 2338.7937;
                    } else {
                        var47 = -11260.572;
                    }
                } else {
                    if (input[3] < 26.494326) {
                        var47 = -7586.2666;
                    } else {
                        var47 = 9958.282;
                    }
                }
            } else {
                if (input[5] < 6.4423933) {
                    if (input[4] < 61.187885) {
                        var47 = -15900.1045;
                    } else {
                        var47 = -1508.5066;
                    }
                } else {
                    if (input[0] < 111.0) {
                        var47 = 1578.0709;
                    } else {
                        var47 = 19000.096;
                    }
                }
            }
        }
    } else {
        if (input[5] < 6.9515424) {
            if (input[5] < 6.878) {
                if (input[1] < 9.649) {
                    if (input[5] < 6.046462) {
                        var47 = 18165.48;
                    } else {
                        var47 = 1467.054;
                    }
                } else {
                    if (input[3] < 19.346) {
                        var47 = -4012.4512;
                    } else {
                        var47 = -719.2038;
                    }
                }
            } else {
                if (input[2] < 209.09291) {
                    if (input[0] < 14.58329) {
                        var47 = -2679.6658;
                    } else {
                        var47 = -22528.566;
                    }
                } else {
                    if (input[5] < 6.915717) {
                        var47 = -4371.3613;
                    } else {
                        var47 = 1495.0575;
                    }
                }
            }
        } else {
            if (input[4] < 66.393) {
                if (input[2] < 222.8815) {
                    if (input[5] < 7.3965125) {
                        var47 = 8504.783;
                    } else {
                        var47 = -12340.756;
                    }
                } else {
                    if (input[2] < 265.0) {
                        var47 = -4258.399;
                    } else {
                        var47 = 167.33212;
                    }
                }
            } else {
                if (input[0] < 69.0) {
                    if (input[0] < 9.0) {
                        var47 = 2788.164;
                    } else {
                        var47 = -8835.575;
                    }
                } else {
                    if (input[2] < 265.0) {
                        var47 = 19080.102;
                    } else {
                        var47 = -7.2829103;
                    }
                }
            }
        }
    }
    float var48;
    if (input[2] < 107.78973) {
        if (input[2] < 98.69333) {
            if (input[4] < 60.43509) {
                if (input[2] < 1.0) {
                    if (input[1] < 71.86359) {
                        var48 = -2887.2295;
                    } else {
                        var48 = 4943.377;
                    }
                } else {
                    if (input[1] < 31.035454) {
                        var48 = 711.4618;
                    } else {
                        var48 = -450.57974;
                    }
                }
            } else {
                if (input[1] < 79.52621) {
                    if (input[1] < 68.776) {
                        var48 = 240.46492;
                    } else {
                        var48 = 2563.4204;
                    }
                } else {
                    if (input[1] < 86.0) {
                        var48 = -4171.025;
                    } else {
                        var48 = 2872.8455;
                    }
                }
            }
        } else {
            if (input[5] < 7.0933285) {
                if (input[1] < 57.0) {
                    if (input[4] < 55.887) {
                        var48 = 12334.13;
                    } else {
                        var48 = 2032.646;
                    }
                } else {
                    if (input[0] < 92.859344) {
                        var48 = -12657.336;
                    } else {
                        var48 = 1354.1887;
                    }
                }
            } else {
                if (input[5] < 7.365575) {
                    if (input[5] < 7.2848873) {
                        var48 = 11090.551;
                    } else {
                        var48 = 45441.906;
                    }
                } else {
                    if (input[0] < 98.72169) {
                        var48 = 1847.613;
                    } else {
                        var48 = -9003.879;
                    }
                }
            }
        }
    } else {
        if (input[4] < 48.237) {
            if (input[5] < 7.2437754) {
                if (input[0] < 70.6058) {
                    if (input[0] < 69.0) {
                        var48 = -2611.3252;
                    } else {
                        var48 = 12279.734;
                    }
                } else {
                    if (input[2] < 176.10364) {
                        var48 = -14407.393;
                    } else {
                        var48 = -3596.8435;
                    }
                }
            } else {
                if (input[5] < 7.937649) {
                    var48 = 16634.629;
                } else {
                    var48 = 1505.2711;
                }
            }
        } else {
            if (input[4] < 49.091248) {
                if (input[3] < 29.237621) {
                    if (input[2] < 112.69621) {
                        var48 = -1315.315;
                    } else {
                        var48 = 22244.633;
                    }
                } else {
                    if (input[4] < 48.625385) {
                        var48 = 7123.06;
                    } else {
                        var48 = -9801.242;
                    }
                }
            } else {
                if (input[4] < 62.728535) {
                    if (input[1] < 60.40199) {
                        var48 = -913.9817;
                    } else {
                        var48 = 1880.8203;
                    }
                } else {
                    if (input[4] < 64.911) {
                        var48 = -5394.0674;
                    } else {
                        var48 = -898.3781;
                    }
                }
            }
        }
    }
    float var49;
    if (input[1] < 5.729007) {
        if (input[3] < 33.7315) {
            if (input[5] < 7.4391994) {
                if (input[5] < 7.2615433) {
                    if (input[0] < 32.0) {
                        var49 = 3553.822;
                    } else {
                        var49 = -510.91684;
                    }
                } else {
                    if (input[5] < 7.3965125) {
                        var49 = -8475.088;
                    } else {
                        var49 = 70.84844;
                    }
                }
            } else {
                if (input[2] < 52.0) {
                    if (input[0] < 13.997322) {
                        var49 = 3821.93;
                    } else {
                        var49 = 12179.139;
                    }
                } else {
                    var49 = -2057.0608;
                }
            }
        } else {
            if (input[0] < 39.654034) {
                if (input[2] < 2.1954777) {
                    var49 = -2615.0244;
                } else {
                    var49 = 3970.2737;
                }
            } else {
                var49 = 26106.67;
            }
        }
    } else {
        if (input[5] < 8.869533) {
            if (input[5] < 4.5161543) {
                if (input[2] < 27.694656) {
                    if (input[3] < 31.094688) {
                        var49 = -1885.213;
                    } else {
                        var49 = 6157.7075;
                    }
                } else {
                    if (input[2] < 171.74876) {
                        var49 = -8784.875;
                    } else {
                        var49 = -571.6336;
                    }
                }
            } else {
                if (input[0] < 191.0) {
                    if (input[0] < 1.1725864) {
                        var49 = 1062.7473;
                    } else {
                        var49 = -10.639175;
                    }
                } else {
                    if (input[5] < 6.679226) {
                        var49 = 1308.4246;
                    } else {
                        var49 = -7710.374;
                    }
                }
            }
        } else {
            if (input[2] < 31.056194) {
                if (input[0] < 40.0) {
                    if (input[0] < 30.0) {
                        var49 = -3539.8333;
                    } else {
                        var49 = 1045.5933;
                    }
                } else {
                    var49 = -7398.7993;
                }
            } else {
                if (input[0] < 1.1725864) {
                    if (input[2] < 41.304405) {
                        var49 = 686.6004;
                    } else {
                        var49 = -957.9782;
                    }
                } else {
                    var49 = 5756.586;
                }
            }
        }
    }
    float var50;
    if (input[2] < 14.318071) {
        if (input[1] < 35.007843) {
            if (input[4] < 82.89754) {
                if (input[5] < 4.992127) {
                    if (input[5] < 4.5161543) {
                        var50 = -358.94083;
                    } else {
                        var50 = 22248.719;
                    }
                } else {
                    if (input[4] < 78.796) {
                        var50 = -1294.1482;
                    } else {
                        var50 = -9864.613;
                    }
                }
            } else {
                if (input[5] < 5.1338725) {
                    var50 = -26830.248;
                } else {
                    if (input[0] < 110.15318) {
                        var50 = 2470.9214;
                    } else {
                        var50 = -10516.178;
                    }
                }
            }
        } else {
            if (input[1] < 51.0) {
                if (input[1] < 50.348312) {
                    if (input[4] < 67.18) {
                        var50 = 398.81116;
                    } else {
                        var50 = 5272.5903;
                    }
                } else {
                    if (input[4] < 60.43509) {
                        var50 = 8302.395;
                    } else {
                        var50 = 26049.232;
                    }
                }
            } else {
                if (input[4] < 67.18) {
                    if (input[1] < 63.86) {
                        var50 = -1136.8213;
                    } else {
                        var50 = 3800.172;
                    }
                } else {
                    if (input[2] < 1.0) {
                        var50 = 2825.2966;
                    } else {
                        var50 = -7453.1245;
                    }
                }
            }
        }
    } else {
        if (input[2] < 16.438295) {
            if (input[3] < 20.619783) {
                if (input[3] < 20.21071) {
                    if (input[5] < 6.322396) {
                        var50 = -803.2732;
                    } else {
                        var50 = 3669.8684;
                    }
                } else {
                    if (input[0] < 19.3109) {
                        var50 = 3478.3735;
                    } else {
                        var50 = 27100.088;
                    }
                }
            } else {
                if (input[1] < 18.0) {
                    if (input[1] < 15.4032755) {
                        var50 = -1027.9244;
                    } else {
                        var50 = 17306.014;
                    }
                } else {
                    if (input[4] < 78.796) {
                        var50 = -2527.9634;
                    } else {
                        var50 = -9369.822;
                    }
                }
            }
        } else {
            if (input[5] < 4.9) {
                if (input[0] < 138.24232) {
                    if (input[1] < 64.16647) {
                        var50 = -2336.6506;
                    } else {
                        var50 = 3724.3005;
                    }
                } else {
                    if (input[2] < 222.8815) {
                        var50 = -10784.232;
                    } else {
                        var50 = 799.3258;
                    }
                }
            } else {
                if (input[5] < 5.685225) {
                    if (input[2] < 52.524303) {
                        var50 = 2163.8088;
                    } else {
                        var50 = -574.6527;
                    }
                } else {
                    if (input[2] < 46.0) {
                        var50 = -434.7368;
                    } else {
                        var50 = 178.8766;
                    }
                }
            }
        }
    }
    float var51;
    if (input[5] < 6.007) {
        if (input[0] < 40.32462) {
            if (input[1] < 40.82344) {
                if (input[4] < 54.168) {
                    if (input[3] < 26.494326) {
                        var51 = -1986.9513;
                    } else {
                        var51 = 13273.129;
                    }
                } else {
                    if (input[2] < 34.0) {
                        var51 = -369.0212;
                    } else {
                        var51 = 2967.6077;
                    }
                }
            } else {
                if (input[3] < 24.464146) {
                    if (input[1] < 49.280045) {
                        var51 = -4412.848;
                    } else {
                        var51 = 307.91602;
                    }
                } else {
                    if (input[3] < 33.271) {
                        var51 = -3941.6184;
                    } else {
                        var51 = 3507.2654;
                    }
                }
            }
        } else {
            if (input[4] < 59.389484) {
                if (input[1] < 65.89316) {
                    if (input[1] < 39.915737) {
                        var51 = -4069.584;
                    } else {
                        var51 = -227.1327;
                    }
                } else {
                    if (input[0] < 114.0) {
                        var51 = -9600.245;
                    } else {
                        var51 = -585.3781;
                    }
                }
            } else {
                if (input[1] < 68.776) {
                    if (input[1] < 66.986) {
                        var51 = -622.86346;
                    } else {
                        var51 = -9755.241;
                    }
                } else {
                    if (input[3] < 31.939474) {
                        var51 = 2622.4875;
                    } else {
                        var51 = -12908.3125;
                    }
                }
            }
        }
    } else {
        if (input[4] < 68.74849) {
            if (input[2] < 1.0) {
                if (input[0] < 121.17004) {
                    if (input[0] < 80.0) {
                        var51 = -2212.258;
                    } else {
                        var51 = 3116.573;
                    }
                } else {
                    if (input[3] < 24.714176) {
                        var51 = -2440.2522;
                    } else {
                        var51 = -10088.576;
                    }
                }
            } else {
                if (input[2] < 1.2852505) {
                    if (input[4] < 63.642982) {
                        var51 = 2825.0625;
                    } else {
                        var51 = 10348.377;
                    }
                } else {
                    if (input[0] < 43.347652) {
                        var51 = -542.4471;
                    } else {
                        var51 = 774.48364;
                    }
                }
            }
        } else {
            if (input[4] < 69.606) {
                if (input[5] < 7.065) {
                    if (input[3] < 28.947046) {
                        var51 = -4530.149;
                    } else {
                        var51 = -13309.943;
                    }
                } else {
                    if (input[5] < 7.4391994) {
                        var51 = 13322.852;
                    } else {
                        var51 = -4378.2407;
                    }
                }
            } else {
                if (input[4] < 70.47926) {
                    if (input[5] < 6.4665656) {
                        var51 = -3713.917;
                    } else {
                        var51 = 10417.998;
                    }
                } else {
                    if (input[4] < 72.646) {
                        var51 = -3553.2358;
                    } else {
                        var51 = -232.52199;
                    }
                }
            }
        }
    }
    float var52;
    if (input[2] < 302.70154) {
        if (input[3] < 28.471) {
            if (input[3] < 27.824) {
                if (input[0] < 82.484764) {
                    if (input[4] < 54.928) {
                        var52 = -846.88226;
                    } else {
                        var52 = 451.51926;
                    }
                } else {
                    if (input[4] < 53.937) {
                        var52 = 1834.7521;
                    } else {
                        var52 = -804.24615;
                    }
                }
            } else {
                if (input[5] < 6.7) {
                    if (input[4] < 57.80249) {
                        var52 = -3873.2437;
                    } else {
                        var52 = 915.93555;
                    }
                } else {
                    if (input[1] < 28.29886) {
                        var52 = 3064.6123;
                    } else {
                        var52 = -6308.3286;
                    }
                }
            }
        } else {
            if (input[3] < 28.947046) {
                if (input[1] < 70.363686) {
                    if (input[1] < 35.0) {
                        var52 = 2722.5217;
                    } else {
                        var52 = -2293.137;
                    }
                } else {
                    if (input[2] < 222.8815) {
                        var52 = 6090.552;
                    } else {
                        var52 = -2442.935;
                    }
                }
            } else {
                if (input[1] < 66.986) {
                    if (input[2] < 163.0) {
                        var52 = 354.531;
                    } else {
                        var52 = -2945.917;
                    }
                } else {
                    if (input[5] < 6.066255) {
                        var52 = -4134.2695;
                    } else {
                        var52 = -401.1785;
                    }
                }
            }
        }
    } else {
        if (input[3] < 30.692057) {
            if (input[5] < 6.915717) {
                if (input[3] < 25.866056) {
                    var52 = 3167.4255;
                } else {
                    if (input[1] < 63.373) {
                        var52 = -738.6235;
                    } else {
                        var52 = -3033.7202;
                    }
                }
            } else {
                if (input[0] < 257.0) {
                    if (input[0] < 103.0) {
                        var52 = 3124.052;
                    } else {
                        var52 = -562.0319;
                    }
                } else {
                    var52 = -4787.2383;
                }
            }
        } else {
            if (input[4] < 56.44792) {
                var52 = 354.98282;
            } else {
                if (input[3] < 31.333) {
                    var52 = 3967.4885;
                } else {
                    var52 = 1025.5333;
                }
            }
        }
    }
    float var53;
    if (input[3] < 20.967499) {
        if (input[3] < 20.466938) {
            if (input[5] < 6.159965) {
                if (input[2] < 6.815639) {
                    if (input[2] < 1.0) {
                        var53 = -633.33203;
                    } else {
                        var53 = -8315.551;
                    }
                } else {
                    if (input[2] < 85.0) {
                        var53 = 136.44342;
                    } else {
                        var53 = -2719.0833;
                    }
                }
            } else {
                if (input[4] < 53.688843) {
                    if (input[3] < 19.216644) {
                        var53 = 117.16542;
                    } else {
                        var53 = -5294.8267;
                    }
                } else {
                    if (input[4] < 53.937) {
                        var53 = 15950.931;
                    } else {
                        var53 = 1349.6135;
                    }
                }
            }
        } else {
            if (input[1] < 46.346) {
                if (input[1] < 10.059196) {
                    if (input[0] < 25.973791) {
                        var53 = 1068.9344;
                    } else {
                        var53 = 29178.19;
                    }
                } else {
                    if (input[5] < 5.1338725) {
                        var53 = -24824.166;
                    } else {
                        var53 = -2426.7017;
                    }
                }
            } else {
                if (input[5] < 6.56062) {
                    if (input[4] < 46.97937) {
                        var53 = -756.37866;
                    } else {
                        var53 = 18670.8;
                    }
                } else {
                    if (input[2] < 18.05365) {
                        var53 = -16199.446;
                    } else {
                        var53 = 122.604935;
                    }
                }
            }
        }
    } else {
        if (input[3] < 24.348202) {
            if (input[0] < 38.94616) {
                if (input[5] < 6.9651566) {
                    if (input[5] < 6.281144) {
                        var53 = 788.69037;
                    } else {
                        var53 = -2194.328;
                    }
                } else {
                    if (input[5] < 7.1903377) {
                        var53 = 10541.662;
                    } else {
                        var53 = 293.77527;
                    }
                }
            } else {
                if (input[1] < 65.19307) {
                    if (input[2] < 31.964447) {
                        var53 = 926.0492;
                    } else {
                        var53 = -2564.9746;
                    }
                } else {
                    if (input[4] < 77.621) {
                        var53 = -7579.756;
                    } else {
                        var53 = -384.5468;
                    }
                }
            }
        } else {
            if (input[3] < 24.409006) {
                if (input[5] < 6.182233) {
                    if (input[0] < 4.207439) {
                        var53 = 7829.1;
                    } else {
                        var53 = -3259.9011;
                    }
                } else {
                    if (input[1] < 78.0) {
                        var53 = 5540.147;
                    } else {
                        var53 = 21797.535;
                    }
                }
            } else {
                if (input[1] < 56.432) {
                    if (input[4] < 77.621) {
                        var53 = 106.90409;
                    } else {
                        var53 = -937.9221;
                    }
                } else {
                    if (input[0] < 39.0) {
                        var53 = -1684.1245;
                    } else {
                        var53 = 887.32245;
                    }
                }
            }
        }
    }
    float var54;
    if (input[1] < 78.371) {
        if (input[1] < 75.70204) {
            if (input[1] < 75.0) {
                if (input[1] < 73.88119) {
                    if (input[5] < 6.007) {
                        var54 = -349.51437;
                    } else {
                        var54 = 166.14604;
                    }
                } else {
                    if (input[5] < 7.2437754) {
                        var54 = 4648.1963;
                    } else {
                        var54 = -6878.853;
                    }
                }
            } else {
                if (input[2] < 150.75047) {
                    if (input[5] < 5.585289) {
                        var54 = 15347.175;
                    } else {
                        var54 = -2356.5713;
                    }
                } else {
                    if (input[2] < 167.9841) {
                        var54 = -20035.055;
                    } else {
                        var54 = -2038.2406;
                    }
                }
            }
        } else {
            if (input[2] < 1.0) {
                if (input[3] < 23.083572) {
                    var54 = -3563.0837;
                } else {
                    if (input[3] < 28.782078) {
                        var54 = 27002.795;
                    } else {
                        var54 = 848.94147;
                    }
                }
            } else {
                if (input[4] < 82.564514) {
                    if (input[3] < 33.94) {
                        var54 = 1771.1666;
                    } else {
                        var54 = 17579.432;
                    }
                } else {
                    if (input[4] < 84.61588) {
                        var54 = -19487.693;
                    } else {
                        var54 = 3115.7847;
                    }
                }
            }
        }
    } else {
        if (input[4] < 60.50321) {
            if (input[4] < 48.237) {
                if (input[0] < 67.0) {
                    if (input[0] < 54.45779) {
                        var54 = -1058.2097;
                    } else {
                        var54 = 11231.727;
                    }
                } else {
                    if (input[0] < 127.804855) {
                        var54 = -11155.8125;
                    } else {
                        var54 = 322.79233;
                    }
                }
            } else {
                if (input[0] < 119.3437) {
                    if (input[2] < 17.648172) {
                        var54 = 13119.353;
                    } else {
                        var54 = 2728.058;
                    }
                } else {
                    if (input[4] < 52.638) {
                        var54 = -8953.576;
                    } else {
                        var54 = 312.6192;
                    }
                }
            }
        } else {
            if (input[1] < 84.937) {
                if (input[3] < 23.601154) {
                    if (input[3] < 17.039734) {
                        var54 = -1656.3345;
                    } else {
                        var54 = -14672.763;
                    }
                } else {
                    if (input[3] < 29.840708) {
                        var54 = -1529.5454;
                    } else {
                        var54 = -9546.694;
                    }
                }
            } else {
                if (input[5] < 7.2437754) {
                    if (input[4] < 63.99) {
                        var54 = 7266.2935;
                    } else {
                        var54 = -370.75204;
                    }
                } else {
                    if (input[0] < 5.272074) {
                        var54 = 5462.133;
                    } else {
                        var54 = -9966.415;
                    }
                }
            }
        }
    }
    float var55;
    if (input[2] < 302.70154) {
        if (input[1] < 5.729007) {
            if (input[3] < 33.7315) {
                if (input[5] < 7.4391994) {
                    if (input[5] < 7.2615433) {
                        var55 = 609.8291;
                    } else {
                        var55 = -6042.152;
                    }
                } else {
                    if (input[2] < 52.0) {
                        var55 = 8362.183;
                    } else {
                        var55 = -1943.6012;
                    }
                }
            } else {
                if (input[0] < 39.654034) {
                    if (input[2] < 2.1954777) {
                        var55 = -1946.679;
                    } else {
                        var55 = 3505.736;
                    }
                } else {
                    var55 = 23237.305;
                }
            }
        } else {
            if (input[5] < 6.866002) {
                if (input[5] < 6.763) {
                    if (input[1] < 35.509106) {
                        var55 = -260.61423;
                    } else {
                        var55 = 225.48854;
                    }
                } else {
                    if (input[4] < 48.237) {
                        var55 = -6359.4487;
                    } else {
                        var55 = 2070.4102;
                    }
                }
            } else {
                if (input[5] < 6.9960284) {
                    if (input[2] < 74.27537) {
                        var55 = -905.735;
                    } else {
                        var55 = -5384.118;
                    }
                } else {
                    if (input[2] < 64.48997) {
                        var55 = -421.57263;
                    } else {
                        var55 = 1284.2075;
                    }
                }
            }
        }
    } else {
        if (input[3] < 30.692057) {
            if (input[5] < 7.038153) {
                if (input[3] < 25.866056) {
                    var55 = 2738.0132;
                } else {
                    if (input[4] < 55.450592) {
                        var55 = -72.313896;
                    } else {
                        var55 = -2582.2468;
                    }
                }
            } else {
                if (input[3] < 27.955414) {
                    if (input[0] < 148.22476) {
                        var55 = 2780.0742;
                    } else {
                        var55 = -163.49649;
                    }
                } else {
                    if (input[0] < 257.0) {
                        var55 = -619.56396;
                    } else {
                        var55 = -4448.6743;
                    }
                }
            }
        } else {
            if (input[4] < 56.44792) {
                var55 = 126.5629;
            } else {
                var55 = 2992.2065;
            }
        }
    }
    float var56;
    if (input[2] < 107.78973) {
        if (input[2] < 98.69333) {
            if (input[4] < 61.5) {
                if (input[2] < 81.32543) {
                    if (input[0] < 64.0) {
                        var56 = 176.06017;
                    } else {
                        var56 = -722.6839;
                    }
                } else {
                    if (input[1] < 80.13198) {
                        var56 = -2274.6565;
                    } else {
                        var56 = 9465.068;
                    }
                }
            } else {
                if (input[1] < 35.795704) {
                    if (input[0] < 42.754875) {
                        var56 = 1167.3885;
                    } else {
                        var56 = -1217.6462;
                    }
                } else {
                    if (input[0] < 32.0) {
                        var56 = -1542.9305;
                    } else {
                        var56 = 1269.0256;
                    }
                }
            }
        } else {
            if (input[5] < 7.0933285) {
                if (input[1] < 57.0) {
                    if (input[4] < 55.887) {
                        var56 = 10773.322;
                    } else {
                        var56 = 1602.9691;
                    }
                } else {
                    if (input[0] < 92.859344) {
                        var56 = -10744.31;
                    } else {
                        var56 = 983.95984;
                    }
                }
            } else {
                if (input[5] < 7.365575) {
                    if (input[5] < 7.2848873) {
                        var56 = 9443.876;
                    } else {
                        var56 = 39289.805;
                    }
                } else {
                    if (input[0] < 98.72169) {
                        var56 = 1516.9551;
                    } else {
                        var56 = -8174.9956;
                    }
                }
            }
        }
    } else {
        if (input[4] < 48.237) {
            if (input[5] < 7.2437754) {
                if (input[0] < 70.6058) {
                    if (input[0] < 69.0) {
                        var56 = -1945.8456;
                    } else {
                        var56 = 11501.271;
                    }
                } else {
                    if (input[1] < 2.7366288) {
                        var56 = 8114.778;
                    } else {
                        var56 = -10342.76;
                    }
                }
            } else {
                if (input[5] < 7.937649) {
                    if (input[0] < 40.908596) {
                        var56 = 4138.24;
                    } else {
                        var56 = 15833.664;
                    }
                } else {
                    var56 = 1376.8594;
                }
            }
        } else {
            if (input[4] < 49.091248) {
                if (input[3] < 29.237621) {
                    if (input[2] < 112.69621) {
                        var56 = -1319.7762;
                    } else {
                        var56 = 19236.053;
                    }
                } else {
                    if (input[0] < 9.0) {
                        var56 = 9956.039;
                    } else {
                        var56 = -6367.038;
                    }
                }
            } else {
                if (input[3] < 31.767136) {
                    if (input[3] < 28.730688) {
                        var56 = -805.6807;
                    } else {
                        var56 = 1136.9108;
                    }
                } else {
                    if (input[4] < 60.300743) {
                        var56 = -7265.9263;
                    } else {
                        var56 = -1129.3414;
                    }
                }
            }
        }
    }
    float var57;
    if (input[2] < 302.70154) {
        if (input[0] < 155.0) {
            if (input[0] < 150.0) {
                if (input[0] < 126.0) {
                    if (input[2] < 85.0) {
                        var57 = 80.99888;
                    } else {
                        var57 = -534.9616;
                    }
                } else {
                    if (input[2] < 85.0) {
                        var57 = -377.97253;
                    } else {
                        var57 = 2532.9707;
                    }
                }
            } else {
                if (input[4] < 82.564514) {
                    if (input[4] < 60.300743) {
                        var57 = -4618.262;
                    } else {
                        var57 = 303.05466;
                    }
                } else {
                    if (input[1] < 17.0) {
                        var57 = -312.7094;
                    } else {
                        var57 = -18826.666;
                    }
                }
            }
        } else {
            if (input[1] < 42.0) {
                if (input[1] < 37.315727) {
                    if (input[1] < 7.9263062) {
                        var57 = -9663.211;
                    } else {
                        var57 = 3044.6438;
                    }
                } else {
                    if (input[5] < 5.6158624) {
                        var57 = 3517.1724;
                    } else {
                        var57 = 19076.768;
                    }
                }
            } else {
                if (input[2] < 159.0) {
                    if (input[4] < 48.237) {
                        var57 = 13073.893;
                    } else {
                        var57 = -5464.2812;
                    }
                } else {
                    if (input[1] < 81.823) {
                        var57 = 2083.3909;
                    } else {
                        var57 = -3480.682;
                    }
                }
            }
        }
    } else {
        if (input[3] < 30.692057) {
            if (input[3] < 25.866056) {
                if (input[3] < 25.428337) {
                    if (input[0] < 173.0) {
                        var57 = -578.9391;
                    } else {
                        var57 = 479.07132;
                    }
                } else {
                    var57 = 2544.7803;
                }
            } else {
                if (input[5] < 6.915717) {
                    if (input[1] < 63.373) {
                        var57 = -446.1756;
                    } else {
                        var57 = -2565.8123;
                    }
                } else {
                    if (input[3] < 27.955414) {
                        var57 = 1630.5414;
                    } else {
                        var57 = -1065.5131;
                    }
                }
            }
        } else {
            if (input[4] < 56.44792) {
                if (input[0] < 97.46548) {
                    var57 = 37.471584;
                } else {
                    var57 = -37.148438;
                }
            } else {
                var57 = 2532.7234;
            }
        }
    }
    float var58;
    if (input[3] < 20.967499) {
        if (input[2] < 191.0) {
            if (input[2] < 144.59132) {
                if (input[2] < 116.0) {
                    if (input[0] < 110.15318) {
                        var58 = 882.83527;
                    } else {
                        var58 = -1909.515;
                    }
                } else {
                    if (input[0] < 96.0) {
                        var58 = -5909.4077;
                    } else {
                        var58 = 1387.286;
                    }
                }
            } else {
                if (input[5] < 6.522) {
                    if (input[5] < 6.2488275) {
                        var58 = 1454.9055;
                    } else {
                        var58 = 37588.04;
                    }
                } else {
                    if (input[5] < 6.9777) {
                        var58 = -7610.169;
                    } else {
                        var58 = 5695.5454;
                    }
                }
            }
        } else {
            if (input[1] < 97.0) {
                if (input[2] < 216.89438) {
                    var58 = -9548.643;
                } else {
                    var58 = -2660.0293;
                }
            } else {
                if (input[3] < 19.346) {
                    if (input[0] < 15.245295) {
                        var58 = -4262.3994;
                    } else {
                        var58 = -1429.6394;
                    }
                } else {
                    if (input[2] < 216.89438) {
                        var58 = -366.95685;
                    } else {
                        var58 = 4862.581;
                    }
                }
            }
        }
    } else {
        if (input[5] < 7.7) {
            if (input[3] < 24.348202) {
                if (input[3] < 23.970814) {
                    if (input[0] < 35.735455) {
                        var58 = 881.2824;
                    } else {
                        var58 = -857.8188;
                    }
                } else {
                    if (input[0] < 38.94616) {
                        var58 = -583.77893;
                    } else {
                        var58 = -4648.276;
                    }
                }
            } else {
                if (input[3] < 24.409006) {
                    if (input[5] < 6.182233) {
                        var58 = -292.19485;
                    } else {
                        var58 = 6604.1167;
                    }
                } else {
                    if (input[0] < 5.272074) {
                        var58 = 1662.7843;
                    } else {
                        var58 = 9.375738;
                    }
                }
            }
        } else {
            if (input[0] < 84.0) {
                if (input[1] < 13.037827) {
                    if (input[0] < 23.965307) {
                        var58 = -780.825;
                    } else {
                        var58 = 8565.582;
                    }
                } else {
                    if (input[1] < 23.0) {
                        var58 = -7992.4595;
                    } else {
                        var58 = -2846.1992;
                    }
                }
            } else {
                if (input[3] < 32.860783) {
                    if (input[4] < 63.115387) {
                        var58 = -777.6014;
                    } else {
                        var58 = 3617.1047;
                    }
                } else {
                    var58 = 8607.489;
                }
            }
        }
    }
    float var59;
    if (input[1] < 80.0) {
        if (input[1] < 75.70204) {
            if (input[1] < 75.0) {
                if (input[1] < 73.88119) {
                    if (input[5] < 6.007) {
                        var59 = -314.5833;
                    } else {
                        var59 = 149.844;
                    }
                } else {
                    if (input[5] < 7.2437754) {
                        var59 = 3945.9958;
                    } else {
                        var59 = -6086.0137;
                    }
                }
            } else {
                if (input[5] < 6.902751) {
                    if (input[5] < 5.833302) {
                        var59 = 2412.845;
                    } else {
                        var59 = -6111.972;
                    }
                } else {
                    if (input[2] < 16.438295) {
                        var59 = 25573.713;
                    } else {
                        var59 = -497.25113;
                    }
                }
            }
        } else {
            if (input[2] < 1.0) {
                if (input[4] < 50.8) {
                    if (input[0] < 87.0) {
                        var59 = -9978.279;
                    } else {
                        var59 = -996.5942;
                    }
                } else {
                    if (input[4] < 78.0866) {
                        var59 = 23662.453;
                    } else {
                        var59 = 698.325;
                    }
                }
            } else {
                if (input[5] < 7.081) {
                    if (input[3] < 31.652) {
                        var59 = 900.8528;
                    } else {
                        var59 = -7430.643;
                    }
                } else {
                    if (input[5] < 7.3462987) {
                        var59 = 9763.655;
                    } else {
                        var59 = 182.82266;
                    }
                }
            }
        }
    } else {
        if (input[5] < 5.5225325) {
            if (input[3] < 28.471) {
                if (input[0] < 104.0) {
                    if (input[4] < 46.174072) {
                        var59 = -6052.8906;
                    } else {
                        var59 = 2872.6191;
                    }
                } else {
                    if (input[4] < 47.741) {
                        var59 = 1370.2306;
                    } else {
                        var59 = -12721.194;
                    }
                }
            } else {
                if (input[2] < 135.0) {
                    if (input[5] < 4.9) {
                        var59 = -5313.606;
                    } else {
                        var59 = 15849.153;
                    }
                } else {
                    if (input[0] < 72.0) {
                        var59 = -15477.593;
                    } else {
                        var59 = 5627.3687;
                    }
                }
            }
        } else {
            if (input[3] < 28.782078) {
                if (input[3] < 28.76) {
                    if (input[2] < 32.17012) {
                        var59 = 2509.057;
                    } else {
                        var59 = -868.32007;
                    }
                } else {
                    if (input[2] < 196.0) {
                        var59 = 11820.566;
                    } else {
                        var59 = -2034.1521;
                    }
                }
            } else {
                if (input[1] < 86.0) {
                    if (input[4] < 63.314106) {
                        var59 = -1927.8389;
                    } else {
                        var59 = -8187.7803;
                    }
                } else {
                    if (input[4] < 87.45126) {
                        var59 = 689.2716;
                    } else {
                        var59 = -12104.8;
                    }
                }
            }
        }
    }
    return NAN + (var0 + var1 + var2 + var3 + var4 + var5 + var6 + var7 + var8 + var9 + var10 + var11 + var12 + var13 + var14 + var15 + var16 + var17 + var18 + var19 + var20 + var21 + var22 + var23 + var24 + var25 + var26 + var27 + var28 + var29 + var30 + var31 + var32 + var33 + var34 + var35 + var36 + var37 + var38 + var39 + var40 + var41 + var42 + var43 + var44 + var45 + var46 + var47 + var48 + var49 + var50 + var51 + var52 + var53 + var54 + var55 + var56 + var57 + var58 + var59);
}
