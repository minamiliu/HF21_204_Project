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
 52;
 -0.31526;0.13174;0.42995;,
 0.28293;0.13174;0.42995;,
 0.28293;0.13174;-0.33767;,
 -0.31526;0.13174;-0.33767;,
 -0.31526;-0.09671;-0.33767;,
 0.28293;-0.09671;-0.33767;,
 0.28293;-0.09671;0.42995;,
 -0.31526;-0.09671;0.42995;,
 -0.28687;0.12090;-0.30124;,
 0.25453;0.12090;-0.30124;,
 0.25453;-0.08586;-0.30124;,
 -0.28687;-0.08586;-0.30124;,
 0.25453;0.12090;0.39351;,
 -0.28687;0.12090;0.39351;,
 -0.28687;-0.08586;0.39351;,
 0.25453;-0.08586;0.39351;,
 -0.28687;0.12090;0.39351;,
 -0.28687;0.12090;-0.30124;,
 -0.28687;-0.08586;-0.30124;,
 -0.28687;-0.08586;0.39351;,
 0.25453;0.12090;0.39351;,
 0.25453;0.12090;-0.30124;,
 -0.28687;0.12090;-0.30124;,
 -0.28687;-0.08586;-0.30124;,
 0.25453;-0.08586;-0.30124;,
 0.25453;-0.08586;0.39351;,
 -0.31526;0.13174;-0.33767;,
 0.28293;0.13174;-0.33767;,
 -0.31526;-0.09671;0.42995;,
 0.28293;-0.09671;-0.33767;,
 0.28293;0.13174;0.42995;,
 0.28293;0.13174;-0.33767;,
 0.28293;-0.09671;-0.33767;,
 0.28293;-0.09671;0.42995;,
 0.27400;0.12090;0.39351;,
 0.27400;0.12090;-0.30124;,
 0.25453;0.12090;-0.30124;,
 0.27400;-0.08586;0.39351;,
 0.27400;-0.08586;-0.30124;,
 0.25453;-0.08586;-0.30124;,
 0.28293;-0.09671;-0.33767;,
 0.28293;0.13174;-0.33767;,
 0.28293;0.13174;0.42995;,
 0.28293;0.13174;-0.33767;,
 0.28293;-0.09671;-0.33767;,
 0.28293;-0.09671;0.42995;,
 0.26427;0.12090;0.39351;,
 0.26427;0.12090;-0.30124;,
 0.26427;-0.08586;0.39351;,
 0.26427;-0.08586;-0.30124;,
 0.28293;-0.09671;-0.33767;,
 0.28293;0.13174;-0.33767;;
 
 30;
 4;0,1,2,3;,
 4;4,5,6,7;,
 4;8,9,10,11;,
 4;12,13,14,15;,
 4;16,17,18,19;,
 4;16,20,21,22;,
 4;23,24,25,19;,
 4;4,5,6,7;,
 4;0,1,2,3;,
 4;0,26,27,1;,
 4;4,28,6,29;,
 4;30,31,27,1;,
 4;32,33,6,29;,
 4;34,35,36,20;,
 4;37,34,20,25;,
 4;38,37,25,39;,
 4;35,38,39,36;,
 4;33,40,5,6;,
 4;41,30,1,2;,
 4;42,43,31,30;,
 4;44,45,33,32;,
 4;43,42,45,44;,
 4;46,47,35,34;,
 4;48,46,34,37;,
 4;49,48,37,38;,
 4;47,49,38,35;,
 4;47,46,48,49;,
 4;45,50,40,33;,
 4;51,42,30,41;,
 4;51,50,45,42;;
 
 MeshMaterialList {
  2;
  30;
  0,
  0,
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
  1,
  0,
  1,
  0,
  0,
  0,
  0,
  0,
  0,
  1,
  0,
  1,
  0,
  0,
  0,
  0;;
  Material {
   0.329600;0.542400;0.800000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.119480;0.196620;0.290000;;
  }
  Material {
   0.800000;0.800000;0.800000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
 }
 MeshNormals {
  7;
  0.000000;1.000000;0.000000;,
  0.000000;-1.000000;-0.000000;,
  0.000000;0.000000;-1.000000;,
  0.000000;0.000000;1.000000;,
  0.000000;0.000000;0.000000;,
  -1.000000;0.000000;0.000000;,
  1.000000;0.000000;0.000000;;
  30;
  4;0,0,0,0;,
  4;1,1,1,1;,
  4;2,2,2,2;,
  4;3,3,3,3;,
  4;5,5,5,5;,
  4;0,0,0,0;,
  4;1,1,1,1;,
  4;1,1,1,1;,
  4;0,0,0,0;,
  4;1,1,1,1;,
  4;0,0,0,0;,
  4;4,4,4,4;,
  4;4,4,4,4;,
  4;0,0,0,0;,
  4;3,3,3,3;,
  4;1,1,1,1;,
  4;2,2,2,2;,
  4;4,4,4,4;,
  4;4,4,4,4;,
  4;4,4,4,4;,
  4;4,4,4,4;,
  4;6,6,6,6;,
  4;1,1,1,1;,
  4;2,2,2,2;,
  4;0,0,0,0;,
  4;3,3,3,3;,
  4;6,6,6,6;,
  4;4,4,4,4;,
  4;4,4,4,4;,
  4;5,5,5,5;;
 }
 MeshTextureCoords {
  52;
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
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;1.000000;,
  1.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;1.000000;,
  1.000000;1.000000;,
  1.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;1.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  1.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;1.000000;,
  1.000000;1.000000;,
  1.000000;0.000000;,
  0.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;;
 }
}