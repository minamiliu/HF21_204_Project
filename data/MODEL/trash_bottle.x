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
 202;
 0.00000;0.52784;0.00000;,
 0.02760;0.52784;-0.02774;,
 0.00000;0.52784;-0.03922;,
 0.03903;0.52784;0.00000;,
 0.02760;0.52784;0.02774;,
 0.00000;0.52784;0.03922;,
 -0.02760;0.52784;0.02774;,
 -0.03903;0.52784;0.00000;,
 -0.02760;0.52784;-0.02774;,
 0.06113;0.51562;-0.06143;,
 0.00000;0.51562;-0.08688;,
 0.08645;0.51562;0.00000;,
 0.06113;0.51562;0.06143;,
 0.00000;0.51562;0.08688;,
 -0.06113;0.51562;0.06143;,
 -0.08645;0.51562;0.00000;,
 -0.06113;0.51562;-0.06143;,
 0.08955;0.45762;-0.09000;,
 0.00000;0.45762;-0.12728;,
 0.12664;0.45762;0.00000;,
 0.08955;0.45762;0.09000;,
 0.00000;0.45762;0.12728;,
 -0.08955;0.45762;0.09000;,
 -0.12664;0.45762;0.00000;,
 -0.08955;0.45762;-0.09000;,
 0.10854;0.40552;-0.10909;,
 0.00000;0.40552;-0.15427;,
 0.15350;0.40552;0.00000;,
 0.10854;0.40552;0.10909;,
 0.00000;0.40552;0.15427;,
 -0.10854;0.40552;0.10909;,
 -0.15350;0.40552;0.00000;,
 -0.10854;0.40552;-0.10909;,
 0.11521;0.34407;-0.11579;,
 0.00000;0.34407;-0.16375;,
 0.16294;0.34407;0.00000;,
 0.11521;0.34407;0.11579;,
 0.00000;0.34407;0.16375;,
 -0.11521;0.34407;0.11579;,
 -0.16294;0.34407;0.00000;,
 -0.11521;0.34407;-0.11579;,
 0.11521;-0.34407;-0.11579;,
 0.00000;-0.34407;-0.16375;,
 0.16294;-0.34407;0.00000;,
 0.11521;-0.34407;0.11579;,
 -0.00000;-0.34407;0.16375;,
 -0.11521;-0.34407;0.11579;,
 -0.16294;-0.34407;0.00000;,
 -0.11521;-0.34407;-0.11579;,
 0.00000;0.50269;0.00000;,
 0.00000;0.50269;-0.07600;,
 0.05374;0.50269;-0.05374;,
 0.00000;0.50269;0.00000;,
 0.07600;0.50269;0.00000;,
 0.00000;0.50269;0.00000;,
 0.05374;0.50269;0.05374;,
 0.00000;0.50269;0.00000;,
 0.00000;0.50269;0.07600;,
 0.00000;0.50269;0.00000;,
 -0.05374;0.50269;0.05374;,
 0.00000;0.50269;0.00000;,
 -0.07600;0.50269;0.00000;,
 0.00000;0.50269;0.00000;,
 -0.05374;0.50269;-0.05374;,
 0.00000;0.50269;0.00000;,
 0.00000;0.50269;-0.07600;,
 0.08083;-0.33660;-0.08153;,
 0.00000;-0.33659;-0.11525;,
 0.11436;-0.33661;0.00000;,
 0.08083;-0.33660;0.08153;,
 -0.00000;-0.33659;0.11525;,
 -0.08083;-0.33660;0.08153;,
 -0.11436;-0.33661;0.00000;,
 -0.08083;-0.33660;-0.08153;,
 -0.03412;-0.31456;0.03284;,
 0.00000;-0.31450;0.04672;,
 -0.03378;-0.34032;0.03255;,
 0.00000;-0.34019;0.04628;,
 -0.04796;-0.31462;0.00000;,
 -0.04753;-0.34044;0.00000;,
 -0.03412;-0.31456;-0.03284;,
 -0.03378;-0.34032;-0.03255;,
 0.00000;-0.31450;-0.04672;,
 0.00000;-0.34019;-0.04628;,
 0.03412;-0.31456;-0.03284;,
 0.03378;-0.34031;-0.03255;,
 0.04796;-0.31462;0.00000;,
 0.04753;-0.34043;0.00000;,
 0.03412;-0.31456;0.03284;,
 0.03378;-0.34032;0.03255;,
 -0.02885;-0.32220;0.02778;,
 0.00000;-0.32200;0.03942;,
 -0.04066;-0.32239;0.00000;,
 -0.02885;-0.32220;-0.02778;,
 0.00000;-0.32200;-0.03942;,
 0.02885;-0.32220;-0.02778;,
 0.04066;-0.32239;-0.00000;,
 0.02885;-0.32220;0.02778;,
 -0.00444;-0.29483;0.00378;,
 0.00000;-0.29472;0.00538;,
 -0.00624;-0.29494;0.00000;,
 -0.00444;-0.29483;-0.00378;,
 0.00000;-0.29472;-0.00538;,
 0.00443;-0.29483;-0.00378;,
 0.00624;-0.29494;0.00000;,
 0.00443;-0.29483;0.00378;,
 0.01466;-0.27710;-0.01483;,
 0.00000;-0.27709;-0.02098;,
 0.02072;-0.27711;0.00000;,
 0.01466;-0.27710;0.01483;,
 -0.00000;-0.27709;0.02098;,
 -0.01466;-0.27710;0.01483;,
 -0.02072;-0.27711;0.00000;,
 -0.01466;-0.27710;-0.01483;,
 -0.00000;-0.27480;0.00000;,
 0.00000;0.52195;0.00000;,
 0.00000;0.50721;-0.06238;,
 0.04411;0.50721;-0.04411;,
 0.00000;0.52195;0.00000;,
 0.06238;0.50721;0.00000;,
 0.00000;0.52195;0.00000;,
 0.04411;0.50721;0.04411;,
 0.00000;0.52195;0.00000;,
 0.00000;0.50721;0.06238;,
 0.00000;0.52195;0.00000;,
 -0.04411;0.50721;0.04411;,
 0.00000;0.52195;0.00000;,
 -0.06238;0.50721;0.00000;,
 0.00000;0.52195;0.00000;,
 -0.04411;0.50721;-0.04411;,
 0.00000;0.52195;0.00000;,
 0.00000;0.50721;-0.06238;,
 0.00000;0.62951;-0.00100;,
 0.05233;0.62951;-0.05333;,
 0.00000;0.62951;-0.07500;,
 0.00000;0.62951;-0.00100;,
 0.07400;0.62951;-0.00100;,
 0.00000;0.62951;-0.00100;,
 0.05233;0.62951;0.05133;,
 0.00000;0.62951;-0.00100;,
 0.00000;0.62951;0.07300;,
 0.00000;0.62951;-0.00100;,
 -0.05233;0.62951;0.05133;,
 0.00000;0.62951;-0.00100;,
 -0.07400;0.62951;-0.00100;,
 0.00000;0.62951;-0.00100;,
 -0.05233;0.62951;-0.05333;,
 0.00000;0.62951;-0.00100;,
 0.00000;0.62951;-0.07500;,
 0.05233;0.54988;-0.05333;,
 0.00000;0.55079;-0.07500;,
 0.07400;0.54959;-0.00100;,
 0.05233;0.55010;0.05133;,
 0.00000;0.55111;0.07300;,
 -0.05233;0.55203;0.05133;,
 -0.07400;0.55231;-0.00100;,
 -0.05233;0.55180;-0.05333;,
 0.00000;0.55079;-0.07500;,
 0.03066;0.54988;-0.03166;,
 0.00000;0.55079;-0.04436;,
 0.04336;0.54959;-0.00100;,
 0.03066;0.55010;0.02966;,
 0.00000;0.55111;0.04236;,
 -0.03066;0.55203;0.02966;,
 -0.04336;0.55231;-0.00100;,
 -0.03066;0.55180;-0.03166;,
 0.00000;0.55079;-0.04436;,
 0.02862;0.54788;-0.02964;,
 -0.00002;0.54885;-0.04147;,
 0.04050;0.54758;-0.00100;,
 0.02862;0.54812;0.02764;,
 -0.00002;0.54918;0.03946;,
 -0.02860;0.55014;0.02758;,
 -0.04043;0.55044;-0.00100;,
 -0.02861;0.54991;-0.02958;,
 -0.00002;0.54885;-0.04147;,
 0.00000;0.55167;-0.00100;,
 -0.00002;0.52947;-0.05798;,
 0.04030;0.52942;-0.04132;,
 0.00000;0.55167;-0.00100;,
 0.05702;0.52940;-0.00100;,
 0.00000;0.55167;-0.00100;,
 0.04030;0.52943;0.03932;,
 0.00000;0.55167;-0.00100;,
 -0.00002;0.52949;0.05597;,
 0.00000;0.55167;-0.00100;,
 -0.04027;0.52954;0.03925;,
 0.00000;0.55167;-0.00100;,
 -0.05693;0.52955;-0.00100;,
 0.00000;0.55167;-0.00100;,
 -0.04028;0.52953;-0.04126;,
 0.00000;0.55167;-0.00100;,
 -0.00002;0.52947;-0.05798;,
 0.02676;0.54553;-0.02779;,
 -0.00004;0.54656;-0.03880;,
 0.03789;0.54521;-0.00100;,
 0.02674;0.54578;0.02579;,
 -0.00004;0.54691;0.03678;,
 -0.02669;0.54792;0.02566;,
 -0.03771;0.54824;-0.00099;,
 -0.02671;0.54768;-0.02766;,
 -0.00004;0.54656;-0.03880;;
 
 175;
 3;0,1,2;,
 3;0,3,1;,
 3;0,4,3;,
 3;0,5,4;,
 3;0,6,5;,
 3;0,7,6;,
 3;0,8,7;,
 4;2,1,9,10;,
 4;1,3,11,9;,
 4;3,4,12,11;,
 4;4,5,13,12;,
 4;5,6,14,13;,
 4;6,7,15,14;,
 4;7,8,16,15;,
 4;8,2,10,16;,
 4;10,9,17,18;,
 4;9,11,19,17;,
 4;11,12,20,19;,
 4;12,13,21,20;,
 4;13,14,22,21;,
 4;14,15,23,22;,
 4;15,16,24,23;,
 4;16,10,18,24;,
 4;18,17,25,26;,
 4;17,19,27,25;,
 4;19,20,28,27;,
 4;20,21,29,28;,
 4;21,22,30,29;,
 4;22,23,31,30;,
 4;23,24,32,31;,
 4;24,18,26,32;,
 4;26,25,33,34;,
 4;25,27,35,33;,
 4;27,28,36,35;,
 4;28,29,37,36;,
 4;29,30,38,37;,
 4;30,31,39,38;,
 4;31,32,40,39;,
 4;32,26,34,40;,
 4;34,33,41,42;,
 4;33,35,43,41;,
 4;35,36,44,43;,
 4;36,37,45,44;,
 4;37,38,46,45;,
 4;38,39,47,46;,
 4;39,40,48,47;,
 4;40,34,42,48;,
 3;49,50,51;,
 3;52,51,53;,
 3;54,53,55;,
 3;56,55,57;,
 3;58,57,59;,
 3;60,59,61;,
 3;62,61,63;,
 3;64,63,65;,
 4;66,67,42,41;,
 4;68,66,41,43;,
 4;69,68,43,44;,
 4;70,69,44,45;,
 4;71,70,45,46;,
 4;72,71,46,47;,
 4;73,72,47,48;,
 4;67,73,48,42;,
 4;74,75,67,66;,
 4;75,74,76,77;,
 4;78,74,66,68;,
 4;74,78,79,76;,
 4;80,78,68,69;,
 4;78,80,81,79;,
 4;82,80,69,70;,
 4;80,82,83,81;,
 4;84,82,70,71;,
 4;82,84,85,83;,
 4;86,84,71,72;,
 4;84,86,87,85;,
 4;88,86,72,73;,
 4;86,88,89,87;,
 4;75,88,73,67;,
 4;88,75,77,89;,
 4;77,76,90,91;,
 4;76,79,92,90;,
 4;79,81,93,92;,
 4;81,83,94,93;,
 4;83,85,95,94;,
 4;85,87,96,95;,
 4;87,89,97,96;,
 4;89,77,91,97;,
 4;91,90,98,99;,
 4;90,92,100,98;,
 4;92,93,101,100;,
 4;93,94,102,101;,
 4;94,95,103,102;,
 4;95,96,104,103;,
 4;96,97,105,104;,
 4;97,91,99,105;,
 4;99,98,106,107;,
 4;98,100,108,106;,
 4;100,101,109,108;,
 4;101,102,110,109;,
 4;102,103,111,110;,
 4;103,104,112,111;,
 4;104,105,113,112;,
 4;105,99,107,113;,
 3;107,106,114;,
 3;106,108,114;,
 3;108,109,114;,
 3;109,110,114;,
 3;110,111,114;,
 3;111,112,114;,
 3;112,113,114;,
 3;113,107,114;,
 3;115,116,117;,
 3;118,117,119;,
 3;120,119,121;,
 3;122,121,123;,
 3;124,123,125;,
 3;126,125,127;,
 3;128,127,129;,
 3;130,129,131;,
 3;132,133,134;,
 3;135,136,133;,
 3;137,138,136;,
 3;139,140,138;,
 3;141,142,140;,
 3;143,144,142;,
 3;145,146,144;,
 3;147,148,146;,
 4;149,150,134,133;,
 4;151,149,133,136;,
 4;152,151,136,138;,
 4;153,152,138,140;,
 4;154,153,140,142;,
 4;155,154,142,144;,
 4;156,155,144,146;,
 4;157,156,146,148;,
 4;158,159,150,149;,
 4;160,158,149,151;,
 4;161,160,151,152;,
 4;162,161,152,153;,
 4;163,162,153,154;,
 4;164,163,154,155;,
 4;165,164,155,156;,
 4;166,165,156,157;,
 4;167,168,159,158;,
 4;169,167,158,160;,
 4;170,169,160,161;,
 4;171,170,161,162;,
 4;172,171,162,163;,
 4;173,172,163,164;,
 4;174,173,164,165;,
 4;175,174,165,166;,
 3;176,177,178;,
 3;179,178,180;,
 3;181,180,182;,
 3;183,182,184;,
 3;185,184,186;,
 3;187,186,188;,
 3;189,188,190;,
 3;191,190,192;,
 4;193,194,168,167;,
 4;193,178,177,194;,
 4;195,193,167,169;,
 4;195,180,178,193;,
 4;196,195,169,170;,
 4;196,182,180,195;,
 4;197,196,170,171;,
 4;197,184,182,196;,
 4;198,197,171,172;,
 4;198,186,184,197;,
 4;199,198,172,173;,
 4;199,188,186,198;,
 4;200,199,173,174;,
 4;200,190,188,199;,
 4;201,200,174,175;,
 4;201,192,190,200;;
 
 MeshMaterialList {
  2;
  175;
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
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
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
  0;;
  Material {
   0.586400;0.586400;0.586400;1.000000;;
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
  191;
  0.000000;1.000000;0.000000;,
  0.000000;0.986038;-0.166520;,
  0.088738;0.992133;-0.088305;,
  0.125487;0.992095;0.000000;,
  0.088738;0.992133;0.088305;,
  0.000000;0.992171;0.124888;,
  -0.088738;0.992133;0.088305;,
  -0.125487;0.992095;0.000000;,
  -0.118318;0.985970;-0.117741;,
  0.000000;0.826753;-0.562564;,
  0.399184;0.826216;-0.397517;,
  0.564138;0.825681;0.000000;,
  0.399184;0.826216;0.397517;,
  0.000000;0.826753;0.562564;,
  -0.399184;0.826216;0.397517;,
  -0.564138;0.825681;0.000000;,
  -0.399184;0.826216;-0.397517;,
  0.000000;0.517151;-0.855894;,
  0.606784;0.516208;-0.604435;,
  0.857028;0.515270;0.000000;,
  0.606784;0.516208;0.604435;,
  0.000000;0.517151;0.855894;,
  -0.606784;0.516208;0.604435;,
  -0.857028;0.515270;0.000000;,
  -0.606784;0.516208;-0.604435;,
  0.000000;0.311427;-0.950270;,
  0.673333;0.310748;-0.670864;,
  0.950713;0.310072;0.000000;,
  0.673333;0.310748;0.670864;,
  0.000000;0.311427;0.950270;,
  -0.673333;0.310748;0.670864;,
  -0.950713;0.310072;0.000000;,
  -0.673333;0.310748;-0.670864;,
  0.000000;0.076501;-0.997069;,
  0.706291;0.076315;-0.703796;,
  0.997098;0.076131;0.000000;,
  0.706291;0.076315;0.703796;,
  0.000000;0.076501;0.997069;,
  -0.706291;0.076315;0.703796;,
  -0.997098;0.076131;0.000000;,
  -0.706291;0.076315;-0.703796;,
  0.000000;0.000000;-1.000000;,
  0.708351;0.000000;-0.705860;,
  1.000000;0.000000;0.000000;,
  0.708351;0.000000;0.705860;,
  0.000000;0.000000;1.000000;,
  -0.708351;0.000000;0.705860;,
  -1.000000;0.000000;0.000000;,
  -0.708351;0.000000;-0.705860;,
  0.000000;-1.000000;0.000000;,
  0.000000;-0.988350;0.152200;,
  -0.107772;-0.988362;0.107357;,
  -0.152035;-0.988375;0.000000;,
  -0.107772;-0.988362;-0.107357;,
  0.000000;-0.988350;-0.152200;,
  0.107772;-0.988362;-0.107357;,
  0.152035;-0.988375;-0.000000;,
  0.107772;-0.988362;0.107357;,
  -0.847695;-0.025396;-0.529876;,
  -0.578199;-0.027913;-0.815418;,
  -0.641370;-0.023632;-0.766868;,
  -0.707913;-0.001007;0.706299;,
  -0.847695;-0.025428;0.529875;,
  0.707913;-0.001007;0.706299;,
  0.761895;0.003952;0.647688;,
  0.707913;-0.001007;-0.706299;,
  0.000002;-0.016871;0.999858;,
  -0.702370;-0.017077;0.711607;,
  -0.999851;-0.017275;-0.000006;,
  -0.702368;-0.017064;-0.711610;,
  0.000000;-0.016869;-0.999858;,
  0.702372;-0.017076;-0.711605;,
  0.999851;-0.017287;-0.000000;,
  0.702372;-0.017076;0.711605;,
  0.000017;-0.590781;-0.806832;,
  0.564038;-0.593433;-0.574194;,
  0.802779;-0.596276;-0.000000;,
  0.564038;-0.593434;0.574192;,
  -0.000017;-0.590749;0.806855;,
  -0.564047;-0.593406;0.574212;,
  -0.802770;-0.596289;0.000021;,
  -0.564036;-0.593443;-0.574185;,
  0.000032;-0.779958;-0.625832;,
  0.435046;-0.782228;-0.445930;,
  0.619748;-0.784801;-0.000000;,
  0.435046;-0.782228;0.445930;,
  -0.000026;-0.779962;0.625827;,
  -0.435044;-0.782231;0.445926;,
  -0.619741;-0.784806;0.000043;,
  -0.435041;-0.782242;-0.445910;,
  -0.848918;0.114528;-0.515966;,
  -0.583393;0.126116;-0.802339;,
  -0.228813;0.118453;-0.966237;,
  -0.583393;0.126116;0.802339;,
  -0.848918;0.114528;0.515966;,
  0.583376;0.126145;0.802347;,
  0.228842;0.118504;0.966224;,
  0.583383;0.126145;-0.802341;,
  -0.000015;-1.000000;0.000011;,
  0.000000;-0.973201;0.229957;,
  -0.162605;-0.973201;0.162605;,
  -0.229957;-0.973201;0.000000;,
  -0.162605;-0.973201;-0.162605;,
  0.000000;-0.973201;-0.229957;,
  0.162605;-0.973201;-0.162605;,
  0.229957;-0.973201;-0.000000;,
  0.162605;-0.973201;0.162605;,
  0.000000;-1.000000;-0.000000;,
  0.707107;0.000000;-0.707107;,
  1.000000;0.000000;-0.000000;,
  0.707107;0.000000;0.707107;,
  -0.707107;0.000000;0.707107;,
  -1.000000;0.000000;0.000000;,
  -0.707107;0.000000;-0.707107;,
  -0.022304;-0.957168;-0.288671;,
  0.196386;-0.956374;-0.216292;,
  0.292720;-0.956195;0.002647;,
  0.192852;-0.956898;0.217151;,
  -0.022344;-0.958193;0.285247;,
  -0.209670;-0.959196;0.189691;,
  -0.282257;-0.959336;0.002386;,
  -0.213737;-0.958437;-0.188983;,
  -0.022210;-0.795327;-0.605774;,
  0.425537;-0.787966;-0.445004;,
  0.618739;-0.785592;0.002559;,
  0.421236;-0.789785;0.445870;,
  -0.022290;-0.797782;0.602533;,
  -0.429508;-0.804789;0.409679;,
  -0.590617;-0.806948;0.002613;,
  -0.433642;-0.803113;-0.408613;,
  -0.000861;-0.931795;0.362985;,
  -0.257493;-0.931561;0.256695;,
  -0.363782;-0.931484;0.000117;,
  -0.257475;-0.931624;-0.256484;,
  -0.000826;-0.931871;-0.362790;,
  0.255800;-0.932085;-0.256485;,
  0.362088;-0.932144;0.000084;,
  0.255787;-0.932037;0.256669;,
  -0.000907;-1.000000;0.000106;,
  -0.022966;-0.757887;-0.651981;,
  0.458395;-0.748946;-0.478492;,
  0.665925;-0.746014;0.002644;,
  0.453901;-0.751136;0.479341;,
  -0.023050;-0.760801;0.648576;,
  -0.462021;-0.769156;0.441516;,
  -0.635928;-0.771744;0.002712;,
  -0.466294;-0.767207;-0.440413;,
  -0.219563;-0.026127;-0.975249;,
  -0.761895;0.003953;0.647689;,
  -0.531843;0.023465;0.846518;,
  0.847695;-0.025428;0.529875;,
  0.531843;0.023465;0.846518;,
  0.761895;0.003952;-0.647688;,
  0.531843;0.023465;-0.846518;,
  0.847695;-0.025428;-0.529875;,
  -0.000000;-0.351579;-0.936158;,
  0.656929;-0.354171;-0.665588;,
  0.934175;-0.356816;-0.000000;,
  0.656930;-0.354176;0.665585;,
  -0.000007;-0.351499;0.936188;,
  -0.656937;-0.354100;0.665617;,
  -0.934167;-0.356836;-0.000003;,
  -0.656925;-0.354179;-0.665587;,
  -0.228813;0.118453;0.966237;,
  0.848881;0.114536;0.516025;,
  0.228759;0.118454;-0.966249;,
  0.848934;0.114577;-0.515930;,
  0.000000;-0.994093;0.108528;,
  -0.078396;-0.993974;0.076619;,
  -0.110652;-0.993859;0.000000;,
  -0.078396;-0.993974;-0.076619;,
  -0.000043;-0.994093;-0.108528;,
  0.078345;-0.993981;-0.076581;,
  0.110637;-0.993861;0.000044;,
  0.078389;-0.993974;0.076625;,
  -0.021299;-0.999771;-0.001877;,
  -0.010636;-0.999907;-0.008595;,
  -0.002696;-0.999993;0.002583;,
  -0.013370;-0.999867;0.009305;,
  -0.021300;-0.999771;-0.001868;,
  -0.010626;-0.999907;-0.008590;,
  -0.003916;-0.999990;0.002078;,
  -0.014579;-0.999855;0.008796;,
  0.462796;0.759831;-0.456592;,
  0.007474;0.744137;-0.667985;,
  0.644124;0.764921;-0.000762;,
  0.467004;0.755831;0.458942;,
  0.007552;0.738998;0.673665;,
  -0.483459;0.725021;0.490522;,
  -0.693057;0.720882;-0.000976;,
  -0.480197;0.728269;-0.488913;;
  175;
  3;0,2,1;,
  3;0,3,2;,
  3;0,4,3;,
  3;0,5,4;,
  3;0,6,5;,
  3;0,7,6;,
  3;0,8,7;,
  4;1,2,10,9;,
  4;2,3,11,10;,
  4;3,4,12,11;,
  4;4,5,13,12;,
  4;5,6,14,13;,
  4;6,7,15,14;,
  4;7,8,16,15;,
  4;8,1,9,16;,
  4;9,10,18,17;,
  4;10,11,19,18;,
  4;11,12,20,19;,
  4;12,13,21,20;,
  4;13,14,22,21;,
  4;14,15,23,22;,
  4;15,16,24,23;,
  4;16,9,17,24;,
  4;17,18,26,25;,
  4;18,19,27,26;,
  4;19,20,28,27;,
  4;20,21,29,28;,
  4;21,22,30,29;,
  4;22,23,31,30;,
  4;23,24,32,31;,
  4;24,17,25,32;,
  4;25,26,34,33;,
  4;26,27,35,34;,
  4;27,28,36,35;,
  4;28,29,37,36;,
  4;29,30,38,37;,
  4;30,31,39,38;,
  4;31,32,40,39;,
  4;32,25,33,40;,
  4;33,34,42,41;,
  4;34,35,43,42;,
  4;35,36,44,43;,
  4;36,37,45,44;,
  4;37,38,46,45;,
  4;38,39,47,46;,
  4;39,40,48,47;,
  4;40,33,41,48;,
  3;49,49,49;,
  3;49,49,49;,
  3;49,49,49;,
  3;49,49,49;,
  3;49,49,49;,
  3;49,49,49;,
  3;49,49,49;,
  3;49,49,49;,
  4;51,50,50,51;,
  4;52,51,51,52;,
  4;53,52,52,53;,
  4;54,53,53,54;,
  4;55,54,54,55;,
  4;56,55,55,56;,
  4;57,56,56,57;,
  4;50,57,57,50;,
  4;59,58,58,59;,
  4;66,67,67,66;,
  4;60,59,59,147;,
  4;67,148,68,67;,
  4;61,148,149,61;,
  4;60,69,69,68;,
  4;62,61,61,62;,
  4;69,70,70,69;,
  4;63,150,150,63;,
  4;70,71,71,70;,
  4;64,63,63,151;,
  4;71,152,72,71;,
  4;65,152,153,65;,
  4;64,73,73,72;,
  4;154,65,65,154;,
  4;73,66,66,73;,
  4;155,156,75,74;,
  4;156,157,76,75;,
  4;157,158,77,76;,
  4;158,159,78,77;,
  4;159,160,79,78;,
  4;160,161,80,79;,
  4;161,162,81,80;,
  4;162,155,74,81;,
  4;74,75,83,82;,
  4;75,76,84,83;,
  4;76,77,85,84;,
  4;77,78,86,85;,
  4;78,79,87,86;,
  4;79,80,88,87;,
  4;80,81,89,88;,
  4;81,74,82,89;,
  4;90,91,91,90;,
  4;91,92,92,91;,
  4;163,93,93,163;,
  4;93,94,94,93;,
  4;164,95,95,164;,
  4;95,96,96,95;,
  4;165,97,97,165;,
  4;97,166,166,97;,
  3;167,168,98;,
  3;168,169,98;,
  3;169,170,98;,
  3;170,171,98;,
  3;171,172,98;,
  3;172,173,98;,
  3;173,174,98;,
  3;174,167,98;,
  3;107,99,100;,
  3;107,100,101;,
  3;107,101,102;,
  3;107,102,103;,
  3;107,103,104;,
  3;107,104,105;,
  3;107,105,106;,
  3;107,106,99;,
  3;0,0,0;,
  3;0,0,0;,
  3;0,0,0;,
  3;0,0,0;,
  3;0,0,0;,
  3;0,0,0;,
  3;0,0,0;,
  3;0,0,0;,
  4;108,41,41,108;,
  4;109,108,108,109;,
  4;110,109,109,110;,
  4;45,110,110,45;,
  4;111,45,45,111;,
  4;112,111,111,112;,
  4;113,112,112,113;,
  4;41,113,113,41;,
  4;115,114,175,176;,
  4;116,115,176,177;,
  4;117,116,177,178;,
  4;118,117,178,179;,
  4;119,118,179,180;,
  4;120,119,180,181;,
  4;121,120,181,182;,
  4;114,121,182,175;,
  4;123,122,114,115;,
  4;124,123,115,116;,
  4;125,124,116,117;,
  4;126,125,117,118;,
  4;127,126,118,119;,
  4;128,127,119,120;,
  4;129,128,120,121;,
  4;122,129,121,114;,
  3;138,130,131;,
  3;138,131,132;,
  3;138,132,133;,
  3;138,133,134;,
  3;138,134,135;,
  3;138,135,136;,
  3;138,136,137;,
  3;138,137,130;,
  4;140,139,122,123;,
  4;183,183,184,184;,
  4;141,140,123,124;,
  4;185,185,183,183;,
  4;142,141,124,125;,
  4;186,186,185,185;,
  4;143,142,125,126;,
  4;187,187,186,186;,
  4;144,143,126,127;,
  4;188,188,187,187;,
  4;145,144,127,128;,
  4;189,189,188,188;,
  4;146,145,128,129;,
  4;190,190,189,189;,
  4;139,146,129,122;,
  4;184,184,190,190;;
 }
 MeshTextureCoords {
  202;
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.062500;1.000000;,
  0.000000;1.000000;,
  0.125000;1.000000;,
  0.187500;1.000000;,
  0.250000;1.000000;,
  0.312500;1.000000;,
  0.375000;1.000000;,
  0.437500;1.000000;,
  0.500000;1.000000;,
  0.562500;1.000000;,
  0.625000;1.000000;,
  0.687500;1.000000;,
  0.750000;1.000000;,
  0.812500;1.000000;,
  0.875000;1.000000;,
  0.937500;1.000000;,
  1.000000;1.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.062500;1.000000;,
  0.000000;1.000000;,
  0.125000;1.000000;,
  0.187500;1.000000;,
  0.250000;1.000000;,
  0.312500;1.000000;,
  0.375000;1.000000;,
  0.437500;1.000000;,
  0.500000;1.000000;,
  0.562500;1.000000;,
  0.625000;1.000000;,
  0.687500;1.000000;,
  0.750000;1.000000;,
  0.812500;1.000000;,
  0.875000;1.000000;,
  0.937500;1.000000;,
  1.000000;1.000000;,
  0.062500;0.000000;,
  0.125000;0.000000;,
  0.000000;0.000000;,
  0.187500;0.000000;,
  0.250000;0.000000;,
  0.312500;0.000000;,
  0.375000;0.000000;,
  0.437500;0.000000;,
  0.500000;0.000000;,
  0.562500;0.000000;,
  0.625000;0.000000;,
  0.687500;0.000000;,
  0.750000;0.000000;,
  0.812500;0.000000;,
  0.875000;0.000000;,
  0.937500;0.000000;,
  1.000000;0.000000;,
  0.125000;0.674890;,
  0.000000;0.667120;,
  0.250000;0.677320;,
  0.375000;0.672990;,
  0.500000;0.664440;,
  0.625000;0.656670;,
  0.750000;0.654240;,
  0.875000;0.658570;,
  1.000000;0.667120;,
  0.125000;0.674890;,
  0.000000;0.667120;,
  0.250000;0.677320;,
  0.375000;0.672990;,
  0.500000;0.664440;,
  0.625000;0.656670;,
  0.750000;0.654240;,
  0.875000;0.658570;,
  1.000000;0.667120;,
  0.125000;0.674890;,
  0.000000;0.667120;,
  0.250000;0.677320;,
  0.375000;0.672990;,
  0.500000;0.664440;,
  0.625000;0.656670;,
  0.750000;0.654240;,
  0.875000;0.658570;,
  1.000000;0.667120;,
  0.062500;1.000000;,
  0.000000;1.000000;,
  0.125000;1.000000;,
  0.187500;1.000000;,
  0.250000;1.000000;,
  0.312500;1.000000;,
  0.375000;1.000000;,
  0.437500;1.000000;,
  0.500000;1.000000;,
  0.562500;1.000000;,
  0.625000;1.000000;,
  0.687500;1.000000;,
  0.750000;1.000000;,
  0.812500;1.000000;,
  0.875000;1.000000;,
  0.937500;1.000000;,
  1.000000;1.000000;,
  0.125000;0.674890;,
  0.000000;0.667120;,
  0.250000;0.677320;,
  0.375000;0.672990;,
  0.500000;0.664440;,
  0.625000;0.656670;,
  0.750000;0.654240;,
  0.875000;0.658570;,
  1.000000;0.667120;;
 }
}