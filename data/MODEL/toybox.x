xof 0302txt 0064
template Header {
 <3D82AB43-62DA-11cf-AB39-0020AF71E433>
 WORD major;
 WORD minor;
 DWORD flags;
}

template Vector {
 <3D82AB5E-62DA-11cf-AB39-0020AF71E433>
 FLOAT x;
 FLOAT y;
 FLOAT z;
}

template Coords2d {
 <F6F23F44-7686-11cf-8F52-0040333594A3>
 FLOAT u;
 FLOAT v;
}

template Matrix4x4 {
 <F6F23F45-7686-11cf-8F52-0040333594A3>
 array FLOAT matrix[16];
}

template ColorRGBA {
 <35FF44E0-6C7C-11cf-8F52-0040333594A3>
 FLOAT red;
 FLOAT green;
 FLOAT blue;
 FLOAT alpha;
}

template ColorRGB {
 <D3E16E81-7835-11cf-8F52-0040333594A3>
 FLOAT red;
 FLOAT green;
 FLOAT blue;
}

template IndexedColor {
 <1630B820-7842-11cf-8F52-0040333594A3>
 DWORD index;
 ColorRGBA indexColor;
}

template Boolean {
 <4885AE61-78E8-11cf-8F52-0040333594A3>
 WORD truefalse;
}

template Boolean2d {
 <4885AE63-78E8-11cf-8F52-0040333594A3>
 Boolean u;
 Boolean v;
}

template MaterialWrap {
 <4885AE60-78E8-11cf-8F52-0040333594A3>
 Boolean u;
 Boolean v;
}

template TextureFilename {
 <A42790E1-7810-11cf-8F52-0040333594A3>
 STRING filename;
}

template Material {
 <3D82AB4D-62DA-11cf-AB39-0020AF71E433>
 ColorRGBA faceColor;
 FLOAT power;
 ColorRGB specularColor;
 ColorRGB emissiveColor;
 [...]
}

template MeshFace {
 <3D82AB5F-62DA-11cf-AB39-0020AF71E433>
 DWORD nFaceVertexIndices;
 array DWORD faceVertexIndices[nFaceVertexIndices];
}

template MeshFaceWraps {
 <4885AE62-78E8-11cf-8F52-0040333594A3>
 DWORD nFaceWrapValues;
 Boolean2d faceWrapValues;
}

template MeshTextureCoords {
 <F6F23F40-7686-11cf-8F52-0040333594A3>
 DWORD nTextureCoords;
 array Coords2d textureCoords[nTextureCoords];
}

template MeshMaterialList {
 <F6F23F42-7686-11cf-8F52-0040333594A3>
 DWORD nMaterials;
 DWORD nFaceIndexes;
 array DWORD faceIndexes[nFaceIndexes];
 [Material]
}

template MeshNormals {
 <F6F23F43-7686-11cf-8F52-0040333594A3>
 DWORD nNormals;
 array Vector normals[nNormals];
 DWORD nFaceNormals;
 array MeshFace faceNormals[nFaceNormals];
}

template MeshVertexColors {
 <1630B821-7842-11cf-8F52-0040333594A3>
 DWORD nVertexColors;
 array IndexedColor vertexColors[nVertexColors];
}

template Mesh {
 <3D82AB44-62DA-11cf-AB39-0020AF71E433>
 DWORD nVertices;
 array Vector vertices[nVertices];
 DWORD nFaces;
 array MeshFace faces[nFaces];
 [...]
}

Header{
1;
0;
1;
}

Mesh {
 278;
 -114.42098;4.19143;-64.00934;,
 114.77486;4.19143;-64.00934;,
 114.77486;-3.95733;-64.00934;,
 -114.42098;-3.95733;-64.00934;,
 114.77486;4.19143;-64.00934;,
 114.77486;4.19143;83.76299;,
 114.77486;-3.95733;83.76299;,
 114.77486;-3.95733;-64.00934;,
 114.77486;4.19143;83.76299;,
 -114.42098;4.19143;83.76299;,
 -114.42098;-3.95733;83.76299;,
 114.77486;-3.95733;83.76299;,
 -114.42098;4.19143;83.76299;,
 -114.42098;4.19143;-64.00934;,
 -114.42098;-3.95733;-64.00934;,
 -114.42098;-3.95733;83.76299;,
 114.77486;4.19143;-64.00934;,
 -114.42098;4.19143;-64.00934;,
 -114.42098;-3.95733;-64.00934;,
 114.77486;-3.95733;-64.00934;,
 -117.10202;116.36998;-64.00934;,
 -105.88795;116.36998;-64.00934;,
 -105.88795;-4.07431;-64.00934;,
 -117.10202;-4.07431;-64.00934;,
 -105.88795;116.36998;-64.00934;,
 -105.88795;116.36998;83.76299;,
 -105.88795;-4.07431;83.76299;,
 -105.88795;-4.07431;-64.00934;,
 -105.88795;116.36998;83.76299;,
 -117.10202;116.36998;83.76299;,
 -117.10202;-4.07431;83.76299;,
 -105.88795;-4.07431;83.76299;,
 -117.10202;116.36998;83.76299;,
 -117.10202;116.36998;-64.00934;,
 -117.10202;-4.07431;-64.00934;,
 -117.10202;-4.07431;83.76299;,
 -105.88795;116.36998;-64.00934;,
 -117.10202;116.36998;-64.00934;,
 -117.10202;-4.07431;-64.00934;,
 -105.88795;-4.07431;-64.00934;,
 104.77333;116.36998;-64.00934;,
 115.98650;116.36998;-64.00934;,
 115.98650;-4.07431;-64.00934;,
 104.77333;-4.07431;-64.00934;,
 115.98650;116.36998;-64.00934;,
 115.98650;116.36998;83.76299;,
 115.98650;-4.07431;83.76299;,
 115.98650;-4.07431;-64.00934;,
 115.98650;116.36998;83.76299;,
 104.77333;116.36998;83.76299;,
 104.77333;-4.07431;83.76299;,
 115.98650;-4.07431;83.76299;,
 104.77333;116.36998;83.76299;,
 104.77333;116.36998;-64.00934;,
 104.77333;-4.07431;-64.00934;,
 104.77333;-4.07431;83.76299;,
 115.98650;116.36998;-64.00934;,
 104.77333;116.36998;-64.00934;,
 104.77333;-4.07431;-64.00934;,
 115.98650;-4.07431;-64.00934;,
 -116.40780;116.36998;-71.60795;,
 116.24263;116.36998;-71.60795;,
 116.24263;-4.07431;-71.60795;,
 -116.40780;-4.07431;-71.60795;,
 116.24263;116.36998;-71.60795;,
 116.24263;116.36998;-57.36187;,
 116.24263;-4.07431;-57.36187;,
 116.24263;-4.07431;-71.60795;,
 116.24263;116.36998;-57.36187;,
 -116.40780;116.36998;-57.36187;,
 -116.40780;-4.07431;-57.36187;,
 116.24263;-4.07431;-57.36187;,
 -116.40780;116.36998;-57.36187;,
 -116.40780;116.36998;-71.60795;,
 -116.40780;-4.07431;-71.60795;,
 -116.40780;-4.07431;-57.36187;,
 116.24263;116.36998;-71.60795;,
 -116.40780;116.36998;-71.60795;,
 -116.40780;-4.07431;-71.60795;,
 116.24263;-4.07431;-71.60795;,
 -116.40780;116.36998;69.57684;,
 116.24263;116.36998;69.57684;,
 116.24263;-4.07431;69.57684;,
 -116.40780;-4.07431;69.57684;,
 116.24263;116.36998;69.57684;,
 116.24263;116.36998;83.82342;,
 116.24263;-4.07431;83.82342;,
 116.24263;-4.07431;69.57684;,
 116.24263;116.36998;83.82342;,
 -116.40780;116.36998;83.82342;,
 -116.40780;-4.07431;83.82342;,
 116.24263;-4.07431;83.82342;,
 -116.40780;116.36998;83.82342;,
 -116.40780;116.36998;69.57684;,
 -116.40780;-4.07431;69.57684;,
 -116.40780;-4.07431;83.82342;,
 116.24263;116.36998;69.57684;,
 -116.40780;116.36998;69.57684;,
 -116.40780;-4.07431;69.57684;,
 116.24263;-4.07431;69.57684;,
 -112.67336;243.01553;-8.23132;,
 114.24368;241.96295;-7.67553;,
 114.23936;237.93330;-13.33431;,
 -112.67859;238.98582;-13.89009;,
 114.24368;241.96295;-7.67553;,
 113.45636;118.56126;80.21442;,
 113.45162;114.53104;74.55563;,
 114.23936;237.93330;-13.33431;,
 113.45636;118.56126;80.21442;,
 -113.46165;119.61376;79.65820;,
 -113.46636;115.58348;73.99983;,
 113.45162;114.53104;74.55563;,
 -113.46165;119.61376;79.65820;,
 -112.67336;243.01553;-8.23132;,
 -112.67859;238.98582;-13.89009;,
 -113.46636;115.58348;73.99983;,
 114.24368;241.96295;-7.67553;,
 -112.67336;243.01553;-8.23132;,
 -112.67859;238.98582;-13.89009;,
 114.23936;237.93330;-13.33431;,
 0.11272;80.71332;-86.68668;,
 15.91710;35.19698;-87.84781;,
 1.23205;28.73579;-87.91044;,
 0.11272;80.71332;-86.68668;,
 8.07743;80.88278;-86.45900;,
 0.11272;80.71332;-86.68668;,
 15.27163;64.82919;-87.25581;,
 0.11272;80.71332;-86.68668;,
 0.31925;70.64236;-87.07299;,
 0.11272;80.71332;-86.68668;,
 -14.36623;64.18112;-87.13510;,
 0.11272;80.71332;-86.68668;,
 -7.17763;49.46809;-85.09300;,
 0.11272;80.71332;-86.68668;,
 -13.72032;34.54887;-87.72796;,
 0.11272;80.71332;-86.68668;,
 1.23205;28.73579;-87.91044;,
 28.76274;22.87218;-86.19814;,
 0.95524;42.00048;-87.61496;,
 15.50489;49.94881;-84.44368;,
 45.68343;62.95140;-85.47724;,
 -0.05889;88.36673;-84.76581;,
 -42.96021;61.14352;-85.11457;,
 -13.92557;49.30553;-84.32379;,
 -26.00113;21.67482;-85.97568;,
 0.95524;42.00048;-87.61496;,
 37.35265;14.60529;-83.47912;,
 1.22688;30.07329;-84.93130;,
 20.02061;50.02555;-83.35195;,
 53.90771;71.46978;-82.42272;,
 -0.30423;100.17754;-81.60823;,
 -51.52422;69.29448;-81.99201;,
 -18.43180;49.18477;-83.19584;,
 -34.19911;13.04047;-83.18891;,
 1.22688;30.07329;-84.93130;,
 40.37995;11.65377;-80.10433;,
 1.33338;25.83655;-81.56902;,
 21.61079;50.03423;-82.04890;,
 56.80698;74.41255;-78.93018;,
 -0.37969;104.27678;-78.07945;,
 -54.52048;72.10838;-78.47618;,
 -7.13064;49.33266;-78.28732;,
 -37.06730;9.96051;-79.79043;,
 1.33338;25.83655;-81.56902;,
 37.38413;14.46806;-76.58848;,
 1.25792;29.93619;-78.04025;,
 20.14955;49.88198;-76.01630;,
 53.93877;71.33265;-75.53211;,
 -0.27319;100.04047;-74.71764;,
 -51.49323;69.15736;-75.10179;,
 -18.49474;49.03686;-75.85981;,
 -34.16803;12.90382;-76.29787;,
 1.25792;29.93619;-78.04025;,
 28.82010;22.61909;-73.46586;,
 1.01258;41.74696;-74.88231;,
 15.62087;49.76039;-74.88231;,
 45.74078;62.69830;-72.74454;,
 -0.00198;88.11366;-72.03399;,
 -42.90328;60.89042;-72.38234;,
 -13.95575;49.11363;-74.76242;,
 -25.94378;21.42128;-73.24340;,
 1.01258;41.74696;-74.88231;,
 15.99212;34.86620;-71.21214;,
 1.30665;28.40504;-71.27468;,
 8.83932;49.59741;-74.10963;,
 15.34622;64.49847;-70.61974;,
 -0.27879;101.37799;-71.73814;,
 -14.29120;63.85042;-70.49938;,
 -7.16771;49.24730;-74.04453;,
 -13.64572;34.21817;-71.09185;,
 1.30665;28.40504;-71.27468;,
 0.16446;80.48356;-75.11644;,
 0.16446;80.48356;-75.11644;,
 0.16446;80.48356;-75.11644;,
 0.16446;80.48356;-75.11644;,
 0.16446;80.48356;-75.11644;,
 0.16446;80.48356;-75.11644;,
 0.16446;80.48356;-75.11644;,
 0.16446;80.48356;-75.11644;,
 -0.20549;239.75281;15.33943;,
 8.14685;240.39526;13.85273;,
 -0.20549;240.85988;13.49615;,
 -0.20549;239.75281;15.33943;,
 11.60705;239.27243;14.71379;,
 -0.20549;239.75281;15.33943;,
 8.14685;238.15001;15.57528;,
 -0.20549;239.75281;15.33943;,
 -0.20549;237.68530;15.93230;,
 -0.20549;239.75281;15.33943;,
 -8.55827;238.15001;15.57528;,
 -0.20549;239.75281;15.33943;,
 -12.01846;239.27243;14.71379;,
 -0.20549;239.75281;15.33943;,
 -8.55827;240.39526;13.85273;,
 -0.20549;239.75281;15.33943;,
 -0.20549;240.85988;13.49615;,
 15.22765;239.98001;11.34198;,
 -0.20549;240.83934;10.68270;,
 21.62072;237.90642;12.93346;,
 15.22765;235.83194;14.52494;,
 -0.20549;234.97319;15.18378;,
 -15.63949;235.83194;14.52494;,
 -22.03256;237.90642;12.93346;,
 -15.63949;239.98001;11.34198;,
 -0.20549;240.83934;10.68270;,
 19.95982;238.57089;8.18878;,
 -0.20549;239.69370;7.32772;,
 28.31215;235.86140;10.26834;,
 19.95982;233.15141;12.34749;,
 -0.20549;232.02861;13.20899;,
 -20.37080;233.15141;12.34749;,
 -28.72357;235.86140;10.26834;,
 -20.37080;238.57089;8.18878;,
 -0.20549;239.69370;7.32772;,
 21.62072;236.38223;4.87389;,
 -0.20549;237.59732;3.94169;,
 30.66165;233.44940;7.12464;,
 21.62072;230.51559;9.37495;,
 -0.20549;229.30063;10.30759;,
 -22.03256;230.51559;9.37495;,
 -31.07306;233.44940;7.12464;,
 -22.03256;236.38223;4.87389;,
 -0.20549;237.59732;3.94169;,
 19.95982;233.74689;1.90135;,
 -0.20549;234.86887;1.04029;,
 28.31215;231.03651;3.98092;,
 19.95982;228.32700;6.06006;,
 -0.20549;227.20468;6.92155;,
 -20.37080;228.32700;6.06006;,
 -28.72357;231.03651;3.98092;,
 -20.37080;233.74689;1.90135;,
 -0.20549;234.86887;1.04029;,
 15.22765;231.06583;-0.27566;,
 -0.20549;231.92522;-0.93493;,
 21.62072;228.99185;1.31581;,
 15.22765;226.91794;2.90729;,
 -0.20549;226.05904;3.56656;,
 -15.63949;226.91794;2.90729;,
 -22.03256;228.99185;1.31581;,
 -15.63949;231.06583;-0.27566;,
 -0.20549;231.92522;-0.93493;,
 8.14685;228.74779;-1.32644;,
 -0.20549;229.21262;-1.68303;,
 11.60705;227.62552;-0.46495;,
 8.14685;226.50275;0.39654;,
 -0.20549;226.03790;0.75313;,
 -8.55827;226.50275;0.39654;,
 -12.01846;227.62552;-0.46495;,
 -8.55827;228.74779;-1.32644;,
 -0.20549;229.21262;-1.68303;,
 -0.20549;227.14510;-1.09016;,
 -0.20549;227.14510;-1.09016;,
 -0.20549;227.14510;-1.09016;,
 -0.20549;227.14510;-1.09016;,
 -0.20549;227.14510;-1.09016;,
 -0.20549;227.14510;-1.09016;,
 -0.20549;227.14510;-1.09016;,
 -0.20549;227.14510;-1.09016;;
 
 164;
 4;0,1,2,3;,
 4;4,5,6,7;,
 4;8,9,10,11;,
 4;12,13,14,15;,
 4;12,5,16,17;,
 4;18,19,6,15;,
 4;20,21,22,23;,
 4;24,25,26,27;,
 4;28,29,30,31;,
 4;32,33,34,35;,
 4;32,25,36,37;,
 4;38,39,26,35;,
 4;40,41,42,43;,
 4;44,45,46,47;,
 4;48,49,50,51;,
 4;52,53,54,55;,
 4;52,45,56,57;,
 4;58,59,46,55;,
 4;60,61,62,63;,
 4;64,65,66,67;,
 4;68,69,70,71;,
 4;72,73,74,75;,
 4;72,65,76,77;,
 4;78,79,66,75;,
 4;80,81,82,83;,
 4;84,85,86,87;,
 4;88,89,90,91;,
 4;92,93,94,95;,
 4;92,85,96,97;,
 4;98,99,86,95;,
 4;100,101,102,103;,
 4;104,105,106,107;,
 4;108,109,110,111;,
 4;112,113,114,115;,
 4;112,105,116,117;,
 4;118,119,106,115;,
 3;120,121,122;,
 3;123,124,121;,
 3;125,126,124;,
 3;127,128,126;,
 3;129,130,128;,
 3;131,132,130;,
 3;133,134,132;,
 3;135,136,134;,
 4;122,121,137,138;,
 4;121,124,139,137;,
 4;124,126,140,139;,
 4;126,128,141,140;,
 4;128,130,142,141;,
 4;130,132,143,142;,
 4;132,134,144,143;,
 4;134,136,145,144;,
 4;138,137,146,147;,
 4;137,139,148,146;,
 4;139,140,149,148;,
 4;140,141,150,149;,
 4;141,142,151,150;,
 4;142,143,152,151;,
 4;143,144,153,152;,
 4;144,145,154,153;,
 4;147,146,155,156;,
 4;146,148,157,155;,
 4;148,149,158,157;,
 4;149,150,159,158;,
 4;150,151,160,159;,
 4;151,152,161,160;,
 4;152,153,162,161;,
 4;153,154,163,162;,
 4;156,155,164,165;,
 4;155,157,166,164;,
 4;157,158,167,166;,
 4;158,159,168,167;,
 4;159,160,169,168;,
 4;160,161,170,169;,
 4;161,162,171,170;,
 4;162,163,172,171;,
 4;165,164,173,174;,
 4;164,166,175,173;,
 4;166,167,176,175;,
 4;167,168,177,176;,
 4;168,169,178,177;,
 4;169,170,179,178;,
 4;170,171,180,179;,
 4;171,172,181,180;,
 4;174,173,182,183;,
 4;173,175,184,182;,
 4;175,176,185,184;,
 4;176,177,186,185;,
 4;177,178,187,186;,
 4;178,179,188,187;,
 4;179,180,189,188;,
 4;180,181,190,189;,
 3;183,182,191;,
 3;182,184,192;,
 3;184,185,193;,
 3;185,186,194;,
 3;186,187,195;,
 3;187,188,196;,
 3;188,189,197;,
 3;189,190,198;,
 3;199,200,201;,
 3;202,203,200;,
 3;204,205,203;,
 3;206,207,205;,
 3;208,209,207;,
 3;210,211,209;,
 3;212,213,211;,
 3;214,215,213;,
 4;201,200,216,217;,
 4;200,203,218,216;,
 4;203,205,219,218;,
 4;205,207,220,219;,
 4;207,209,221,220;,
 4;209,211,222,221;,
 4;211,213,223,222;,
 4;213,215,224,223;,
 4;217,216,225,226;,
 4;216,218,227,225;,
 4;218,219,228,227;,
 4;219,220,229,228;,
 4;220,221,230,229;,
 4;221,222,231,230;,
 4;222,223,232,231;,
 4;223,224,233,232;,
 4;226,225,234,235;,
 4;225,227,236,234;,
 4;227,228,237,236;,
 4;228,229,238,237;,
 4;229,230,239,238;,
 4;230,231,240,239;,
 4;231,232,241,240;,
 4;232,233,242,241;,
 4;235,234,243,244;,
 4;234,236,245,243;,
 4;236,237,246,245;,
 4;237,238,247,246;,
 4;238,239,248,247;,
 4;239,240,249,248;,
 4;240,241,250,249;,
 4;241,242,251,250;,
 4;244,243,252,253;,
 4;243,245,254,252;,
 4;245,246,255,254;,
 4;246,247,256,255;,
 4;247,248,257,256;,
 4;248,249,258,257;,
 4;249,250,259,258;,
 4;250,251,260,259;,
 4;253,252,261,262;,
 4;252,254,263,261;,
 4;254,255,264,263;,
 4;255,256,265,264;,
 4;256,257,266,265;,
 4;257,258,267,266;,
 4;258,259,268,267;,
 4;259,260,269,268;,
 3;262,261,270;,
 3;261,263,271;,
 3;263,264,272;,
 3;264,265,273;,
 3;265,266,274;,
 3;266,267,275;,
 3;267,268,276;,
 3;268,269,277;;
 
 MeshMaterialList {
  13;
  164;
  1,
  1,
  1,
  1,
  11,
  10,
  8,
  11,
  8,
  10,
  10,
  10,
  8,
  10,
  8,
  11,
  10,
  10,
  10,
  10,
  11,
  10,
  10,
  10,
  11,
  10,
  10,
  10,
  10,
  10,
  10,
  10,
  10,
  10,
  10,
  11,
  0,
  0,
  12,
  12,
  12,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  6,
  0,
  6,
  0,
  6,
  6,
  0,
  6,
  11,
  11,
  11,
  11,
  11,
  11,
  11,
  11,
  11,
  11,
  11,
  11,
  11,
  11,
  11,
  11,
  11,
  11,
  11,
  11,
  11,
  11,
  11,
  11,
  11,
  11,
  11,
  11,
  11,
  11,
  11,
  11,
  11,
  11,
  11,
  11,
  11,
  11,
  11,
  11,
  11,
  11,
  11,
  11,
  11,
  11,
  11,
  11,
  7,
  7,
  1,
  11,
  11,
  1,
  1,
  9,
  7,
  7,
  7,
  7,
  7,
  7,
  7,
  7;;
  Material {
   0.800000;0.784000;0.000000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.800000;0.514400;0.072000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.445600;0.800000;0.235200;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.800000;0.000000;0.006400;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.000000;0.800000;0.109600;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.000000;0.241600;0.800000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.000000;0.775200;0.800000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.800000;0.800000;0.800000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.800000;0.072000;0.737600;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.800000;0.248000;0.000000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.263200;0.800000;0.520800;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.000000;0.432800;0.047200;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   1.000000;1.000000;1.000000;1.000000;;
   0.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
 }
 MeshNormals {
  173;
  0.000000;0.000000;-1.000000;,
  1.000000;0.000000;0.000000;,
  0.000000;0.000000;1.000000;,
  0.005199;0.814557;-0.580060;,
  0.999986;-0.004612;0.002485;,
  -0.005199;-0.814509;0.580128;,
  0.034844;0.000868;-0.999392;,
  -0.004555;0.023439;-0.999715;,
  0.214907;0.089339;-0.972540;,
  0.143561;0.017195;-0.989492;,
  -0.014959;-0.050057;0.998634;,
  0.004909;-0.038230;0.999257;,
  0.012525;-0.038072;0.999197;,
  -0.065226;-0.017237;-0.997722;,
  -0.727233;0.203125;0.655647;,
  0.021923;-0.987086;0.158686;,
  -0.407671;-0.901498;0.145276;,
  0.268327;0.082142;-0.959819;,
  -0.017687;0.069018;-0.997459;,
  -0.009477;0.191950;-0.981359;,
  -0.097494;0.064362;-0.993153;,
  -0.238446;0.077123;-0.968089;,
  -0.169906;0.027917;-0.985065;,
  0.008885;-0.563596;-0.826003;,
  -0.009304;-0.329584;-0.944080;,
  0.568799;0.290545;-0.769448;,
  0.494491;-0.859655;-0.128342;,
  -0.016046;0.445104;-0.895335;,
  -0.250846;0.426262;-0.869124;,
  -0.429960;-0.871150;0.237134;,
  0.015940;-0.328989;-0.944199;,
  0.013807;-0.756783;-0.653520;,
  -0.261985;-0.733546;-0.627116;,
  0.887071;0.432339;-0.161826;,
  0.551480;-0.825549;-0.119742;,
  -0.020673;0.633054;-0.773832;,
  -0.347212;0.589243;-0.729545;,
  -0.377805;-0.735940;0.561832;,
  -0.731096;0.479770;0.485097;,
  0.016834;-0.631232;0.775411;,
  -0.294698;-0.606775;0.738226;,
  0.677127;0.344316;0.650342;,
  0.502302;-0.864635;-0.009912;,
  -0.007931;0.409151;0.912432;,
  -0.242960;0.391337;0.887595;,
  -0.416109;-0.839518;-0.349375;,
  -0.681089;0.475075;-0.557155;,
  0.013143;-0.439784;0.898007;,
  0.136754;0.005768;0.990588;,
  0.246991;0.058685;0.967239;,
  0.442668;-0.895529;0.045530;,
  -0.002141;0.206585;0.978426;,
  -0.101500;-0.039855;0.994037;,
  -0.424783;-0.900885;0.089248;,
  -0.128926;-0.000007;0.991654;,
  0.019351;-0.949556;-0.312999;,
  -0.339500;-0.894405;-0.291169;,
  -0.007531;-0.036978;0.999288;,
  -0.237038;-0.170305;0.956456;,
  0.838478;0.544935;-0.000272;,
  -0.861541;0.507668;0.004521;,
  0.016484;-0.036507;0.999197;,
  -0.103783;0.152838;0.982787;,
  0.004898;-0.045968;0.998931;,
  0.000001;0.608770;0.793347;,
  0.000001;0.964590;0.263755;,
  0.088601;0.906340;0.413155;,
  0.138795;0.602850;0.785689;,
  0.088603;0.164540;0.982383;,
  0.000000;0.005214;0.999986;,
  -0.088601;0.164531;0.982385;,
  -0.138789;0.602851;0.785690;,
  -0.088597;0.906338;0.413161;,
  0.000001;0.985894;-0.167370;,
  0.160565;0.986726;0.024297;,
  0.271588;0.789817;0.549936;,
  0.160566;-0.231894;0.959398;,
  0.000001;-0.416850;0.908975;,
  -0.160566;-0.231914;0.959393;,
  -0.271606;0.326816;0.905219;,
  -0.160564;0.986727;0.024284;,
  0.000001;0.904032;-0.427466;,
  0.208444;0.928034;-0.308714;,
  0.343482;0.922097;-0.178205;,
  0.208461;-0.538407;0.816494;,
  0.000001;-0.646903;0.762573;,
  -0.208460;-0.538403;0.816497;,
  -0.343518;-0.410799;0.844535;,
  -0.208443;0.928032;-0.308719;,
  0.000001;0.793363;-0.608749;,
  0.225588;0.772910;-0.593060;,
  0.378513;0.734331;-0.563460;,
  0.225598;-0.772910;0.593056;,
  0.000001;-0.793377;0.608730;,
  -0.225596;-0.772911;0.593056;,
  -0.378517;-0.734317;0.563474;,
  -0.225587;0.772911;-0.593059;,
  0.000001;0.646921;-0.762557;,
  0.208460;0.538392;-0.816504;,
  0.343529;0.410744;-0.844557;,
  0.208449;-0.928035;0.308706;,
  0.000001;-0.904038;0.427453;,
  -0.208447;-0.928034;0.308709;,
  -0.343503;-0.922089;0.178206;,
  -0.208458;0.538394;-0.816503;,
  0.000002;0.416863;-0.908969;,
  0.160576;0.231910;-0.959392;,
  0.252342;0.035753;-0.966977;,
  0.160562;-0.986727;-0.024271;,
  0.000001;-0.985881;0.167446;,
  -0.160563;-0.986728;-0.024255;,
  -0.252324;-0.943297;-0.215691;,
  -0.160575;0.231912;-0.959392;,
  0.000002;-0.005222;-0.999986;,
  0.088592;-0.164541;-0.982384;,
  0.138792;-0.602907;-0.785646;,
  0.088601;-0.906369;-0.413091;,
  0.000001;-0.964600;-0.263716;,
  -0.088599;-0.906369;-0.413093;,
  -0.138791;-0.602907;-0.785646;,
  -0.088589;-0.164554;-0.982382;,
  0.000001;-0.608823;-0.793306;,
  -1.000000;0.000000;0.000000;,
  0.000000;1.000000;0.000000;,
  0.000000;-1.000000;-0.000000;,
  -0.999986;0.004652;-0.002435;,
  0.000695;0.580123;0.814529;,
  -0.000696;-0.580122;-0.814529;,
  -0.199763;0.017425;0.979689;,
  -0.027207;-0.061714;0.997723;,
  -0.008945;-0.043417;-0.999017;,
  -0.119369;0.120902;-0.985461;,
  0.302323;0.025723;-0.952858;,
  -0.087287;-0.023291;-0.995911;,
  -0.008044;0.138401;-0.990344;,
  0.447308;-0.883097;0.141619;,
  0.003540;-0.340025;-0.940410;,
  0.442893;-0.892810;-0.082080;,
  0.219648;0.438943;-0.871254;,
  -0.427754;-0.896220;-0.117545;,
  -0.385699;0.197200;-0.901304;,
  0.731841;0.348807;-0.585442;,
  0.308151;0.606907;-0.732603;,
  0.288531;-0.721523;-0.629408;,
  0.019707;-0.793187;0.608659;,
  -0.317288;-0.754417;0.574616;,
  0.314801;0.577306;0.753404;,
  -0.013619;0.601747;0.798570;,
  0.227535;0.403982;0.886017;,
  -0.340535;0.559697;0.755497;,
  -0.325781;-0.613412;-0.719439;,
  0.354411;-0.739767;0.571959;,
  0.326703;-0.593176;0.735804;,
  0.108647;-0.034588;0.993478;,
  -0.389077;0.190345;0.901326;,
  -0.242079;0.047998;0.969069;,
  0.104959;0.157407;0.981940;,
  0.251110;-0.159722;0.954690;,
  0.375641;-0.879089;-0.293422;,
  0.002435;0.073622;0.997283;,
  0.618549;0.148578;-0.771571;,
  0.007177;-0.159459;0.987179;,
  -0.632090;0.122113;-0.765213;,
  0.302235;-0.219868;0.927530;,
  0.343521;-0.410793;0.844537;,
  -0.302199;0.952845;0.027601;,
  -0.343480;0.922096;-0.178215;,
  0.378517;-0.734317;0.563474;,
  -0.378512;0.734330;-0.563461;,
  0.343506;-0.922090;0.178198;,
  -0.343526;0.410746;-0.844558;,
  0.252320;-0.943292;-0.215718;,
  -0.252344;0.035772;-0.966976;;
  164;
  4;0,0,0,0;,
  4;1,1,1,1;,
  4;2,2,2,2;,
  4;122,122,122,122;,
  4;123,123,123,123;,
  4;124,124,124,124;,
  4;0,0,0,0;,
  4;1,1,1,1;,
  4;2,2,2,2;,
  4;122,122,122,122;,
  4;123,123,123,123;,
  4;124,124,124,124;,
  4;0,0,0,0;,
  4;1,1,1,1;,
  4;2,2,2,2;,
  4;122,122,122,122;,
  4;123,123,123,123;,
  4;124,124,124,124;,
  4;0,0,0,0;,
  4;1,1,1,1;,
  4;2,2,2,2;,
  4;122,122,122,122;,
  4;123,123,123,123;,
  4;124,124,124,124;,
  4;0,0,0,0;,
  4;1,1,1,1;,
  4;2,2,2,2;,
  4;122,122,122,122;,
  4;123,123,123,123;,
  4;124,124,124,124;,
  4;3,3,3,3;,
  4;4,4,4,4;,
  4;5,5,5,5;,
  4;125,125,125,125;,
  4;126,126,126,126;,
  4;127,127,127,127;,
  3;6,8,7;,
  3;6,9,8;,
  3;128,10,129;,
  3;128,11,10;,
  3;128,12,11;,
  3;6,13,130;,
  3;128,14,14;,
  3;6,7,131;,
  4;15,16,16,15;,
  4;8,9,17,132;,
  4;9,133,18,17;,
  4;133,134,19,18;,
  4;134,130,20,19;,
  4;130,13,21,20;,
  4;13,131,22,21;,
  4;135,15,15,135;,
  4;136,132,24,23;,
  4;132,17,25,24;,
  4;137,137,26,26;,
  4;18,19,27,138;,
  4;19,20,28,27;,
  4;139,139,29,29;,
  4;21,22,30,140;,
  4;22,136,23,30;,
  4;23,24,32,31;,
  4;141,25,33,33;,
  4;26,26,34,34;,
  4;138,27,35,142;,
  4;27,28,36,35;,
  4;29,29,37,37;,
  4;38,38,38,38;,
  4;30,23,31,143;,
  4;144,145,40,39;,
  4;33,33,41,41;,
  4;34,34,42,42;,
  4;146,147,43,148;,
  4;147,149,44,43;,
  4;150,150,45,45;,
  4;46,46,46,46;,
  4;151,144,39,152;,
  4;39,40,48,47;,
  4;41,41,49,48;,
  4;42,42,50,50;,
  4;148,43,51,153;,
  4;43,44,52,51;,
  4;45,45,53,53;,
  4;154,154,54,155;,
  4;152,39,47,54;,
  4;55,56,56,55;,
  4;48,49,57,156;,
  4;49,153,58,57;,
  4;59,59,59,59;,
  4;60,60,60,60;,
  4;52,155,61,157;,
  4;155,54,62,61;,
  4;158,55,55,158;,
  3;159,156,63;,
  3;160,160,160;,
  3;57,58,63;,
  3;58,161,63;,
  3;161,157,63;,
  3;157,61,63;,
  3;162,162,162;,
  3;62,159,63;,
  3;64,66,65;,
  3;64,67,66;,
  3;64,68,67;,
  3;64,69,68;,
  3;64,70,69;,
  3;64,71,70;,
  3;64,72,71;,
  3;64,65,72;,
  4;65,66,74,73;,
  4;66,67,75,74;,
  4;67,68,76,75;,
  4;68,69,77,76;,
  4;69,70,78,77;,
  4;70,71,79,78;,
  4;71,72,80,79;,
  4;72,65,73,80;,
  4;73,74,82,81;,
  4;74,75,83,82;,
  4;163,76,84,164;,
  4;76,77,85,84;,
  4;77,78,86,85;,
  4;78,79,87,86;,
  4;165,80,88,166;,
  4;80,73,81,88;,
  4;81,82,90,89;,
  4;82,83,91,90;,
  4;164,84,92,167;,
  4;84,85,93,92;,
  4;85,86,94,93;,
  4;86,87,95,94;,
  4;166,88,96,168;,
  4;88,81,89,96;,
  4;89,90,98,97;,
  4;90,91,99,98;,
  4;167,92,100,169;,
  4;92,93,101,100;,
  4;93,94,102,101;,
  4;94,95,103,102;,
  4;168,96,104,170;,
  4;96,89,97,104;,
  4;97,98,106,105;,
  4;98,99,107,106;,
  4;169,100,108,171;,
  4;100,101,109,108;,
  4;101,102,110,109;,
  4;102,103,111,110;,
  4;170,104,112,172;,
  4;104,97,105,112;,
  4;105,106,114,113;,
  4;106,107,115,114;,
  4;171,108,116,115;,
  4;108,109,117,116;,
  4;109,110,118,117;,
  4;110,111,119,118;,
  4;172,112,120,119;,
  4;112,105,113,120;,
  3;113,114,121;,
  3;114,115,121;,
  3;115,116,121;,
  3;116,117,121;,
  3;117,118,121;,
  3;118,119,121;,
  3;119,120,121;,
  3;120,113,121;;
 }
 MeshTextureCoords {
  278;
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  0.062500;0.000000;,
  0.125000;0.125000;,
  0.000000;0.125000;,
  0.187500;0.000000;,
  0.250000;0.125000;,
  0.312500;0.000000;,
  0.375000;0.125000;,
  0.437500;0.000000;,
  0.500000;0.125000;,
  0.562500;0.000000;,
  0.625000;0.125000;,
  0.687500;0.000000;,
  0.750000;0.125000;,
  0.812500;0.000000;,
  0.875000;0.125000;,
  0.937500;0.000000;,
  1.000000;0.125000;,
  0.125000;0.250000;,
  0.000000;0.250000;,
  0.250000;0.250000;,
  0.375000;0.250000;,
  0.500000;0.250000;,
  0.625000;0.250000;,
  0.750000;0.250000;,
  0.875000;0.250000;,
  1.000000;0.250000;,
  0.125000;0.375000;,
  0.000000;0.375000;,
  0.250000;0.375000;,
  0.375000;0.375000;,
  0.500000;0.375000;,
  0.625000;0.375000;,
  0.750000;0.375000;,
  0.875000;0.375000;,
  1.000000;0.375000;,
  0.125000;0.500000;,
  0.000000;0.500000;,
  0.250000;0.500000;,
  0.375000;0.500000;,
  0.500000;0.500000;,
  0.625000;0.500000;,
  0.750000;0.500000;,
  0.875000;0.500000;,
  1.000000;0.500000;,
  0.125000;0.625000;,
  0.000000;0.625000;,
  0.250000;0.625000;,
  0.375000;0.625000;,
  0.500000;0.625000;,
  0.625000;0.625000;,
  0.750000;0.625000;,
  0.875000;0.625000;,
  1.000000;0.625000;,
  0.125000;0.750000;,
  0.000000;0.750000;,
  0.250000;0.750000;,
  0.375000;0.750000;,
  0.500000;0.750000;,
  0.625000;0.750000;,
  0.750000;0.750000;,
  0.875000;0.750000;,
  1.000000;0.750000;,
  0.125000;0.875000;,
  0.000000;0.875000;,
  0.250000;0.875000;,
  0.375000;0.875000;,
  0.500000;0.875000;,
  0.625000;0.875000;,
  0.750000;0.875000;,
  0.875000;0.875000;,
  1.000000;0.875000;,
  0.062500;1.000000;,
  0.187500;1.000000;,
  0.312500;1.000000;,
  0.437500;1.000000;,
  0.562500;1.000000;,
  0.687500;1.000000;,
  0.812500;1.000000;,
  0.937500;1.000000;,
  0.062500;0.000000;,
  0.125000;0.125000;,
  0.000000;0.125000;,
  0.187500;0.000000;,
  0.250000;0.125000;,
  0.312500;0.000000;,
  0.375000;0.125000;,
  0.437500;0.000000;,
  0.500000;0.125000;,
  0.562500;0.000000;,
  0.625000;0.125000;,
  0.687500;0.000000;,
  0.750000;0.125000;,
  0.812500;0.000000;,
  0.875000;0.125000;,
  0.937500;0.000000;,
  1.000000;0.125000;,
  0.125000;0.250000;,
  0.000000;0.250000;,
  0.250000;0.250000;,
  0.375000;0.250000;,
  0.500000;0.250000;,
  0.625000;0.250000;,
  0.750000;0.250000;,
  0.875000;0.250000;,
  1.000000;0.250000;,
  0.125000;0.375000;,
  0.000000;0.375000;,
  0.250000;0.375000;,
  0.375000;0.375000;,
  0.500000;0.375000;,
  0.625000;0.375000;,
  0.750000;0.375000;,
  0.875000;0.375000;,
  1.000000;0.375000;,
  0.125000;0.500000;,
  0.000000;0.500000;,
  0.250000;0.500000;,
  0.375000;0.500000;,
  0.500000;0.500000;,
  0.625000;0.500000;,
  0.750000;0.500000;,
  0.875000;0.500000;,
  1.000000;0.500000;,
  0.125000;0.625000;,
  0.000000;0.625000;,
  0.250000;0.625000;,
  0.375000;0.625000;,
  0.500000;0.625000;,
  0.625000;0.625000;,
  0.750000;0.625000;,
  0.875000;0.625000;,
  1.000000;0.625000;,
  0.125000;0.750000;,
  0.000000;0.750000;,
  0.250000;0.750000;,
  0.375000;0.750000;,
  0.500000;0.750000;,
  0.625000;0.750000;,
  0.750000;0.750000;,
  0.875000;0.750000;,
  1.000000;0.750000;,
  0.125000;0.875000;,
  0.000000;0.875000;,
  0.250000;0.875000;,
  0.375000;0.875000;,
  0.500000;0.875000;,
  0.625000;0.875000;,
  0.750000;0.875000;,
  0.875000;0.875000;,
  1.000000;0.875000;,
  0.062500;1.000000;,
  0.187500;1.000000;,
  0.312500;1.000000;,
  0.437500;1.000000;,
  0.562500;1.000000;,
  0.687500;1.000000;,
  0.812500;1.000000;,
  0.937500;1.000000;;
 }
}
