/* Image base: 00100000 */

/* 00104604 leica_filter */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* WARNING: Unknown calling convention */

int leica_filter(u8 *data,int w,int h,int stride,int finishing)

{
  undefined (*pauVar1) [12];
  float *pfVar2;
  float *pfVar3;
  byte *pbVar4;
  undefined8 *puVar5;
  unkbyte9 *pVar6;
  undefined auVar7 [16];
  undefined auVar8 [16];
  undefined8 uVar9;
  undefined auVar10 [16];
  undefined8 uVar11;
  undefined8 uVar12;
  undefined auVar13 [16];
  undefined auVar14 [16];
  undefined auVar15 [16];
  undefined auVar16 [12];
  undefined auVar17 [12];
  unkbyte9 Var18;
  undefined auVar19 [12];
  bool bVar20;
  bool bVar21;
  unkbyte9 *out;
  unkbyte9 *__s;
  unkbyte9 *pVar22;
  long lVar23;
  ulong uVar24;
  uint uVar25;
  int bin;
  float *slot;
  uint uVar26;
  float *sum;
  ulong uVar27;
  usize line;
  ulong uVar28;
  long lVar29;
  int iVar30;
  u8 *puVar31;
  long lVar32;
  u8 *row;
  undefined (*pauVar33) [16];
  float *pfVar34;
  float *pfVar35;
  u8 *puVar36;
  ulong uVar37;
  undefined (*pauVar38) [16];
  float *pfVar39;
  u8 *p;
  int iVar40;
  ulong uVar41;
  ulong uVar42;
  ulong uVar43;
  float *ring;
  undefined (*pauVar44) [16];
  float sy;
  float nv;
  float fVar45;
  float mu;
  float nu;
  float r;
  ulong uVar46;
  float fVar50;
  float fVar51;
  float fVar52;
  undefined auVar47 [16];
  undefined auVar48 [16];
  undefined auVar49 [16];
  float fVar53;
  float g;
  float fVar57;
  float fVar58;
  float fVar59;
  undefined auVar54 [16];
  undefined auVar55 [16];
  undefined auVar56 [16];
  float fVar60;
  float vu;
  float au;
  float fVar62;
  float fVar63;
  float fVar64;
  undefined auVar61 [16];
  float b_1;
  float fVar65;
  undefined8 uVar66;
  double dVar67;
  float fVar72;
  float fVar73;
  float fVar74;
  float fVar75;
  float fVar76;
  float fVar77;
  undefined auVar68 [16];
  undefined auVar69 [16];
  undefined auVar70 [16];
  undefined auVar71 [16];
  float d;
  float fVar78;
  float fVar82;
  float fVar83;
  float fVar84;
  undefined auVar79 [16];
  float fVar85;
  undefined auVar80 [16];
  undefined auVar81 [16];
  float fVar89;
  float yy;
  float fVar86;
  float fVar87;
  float fVar88;
  float fVar92;
  float fVar93;
  float fVar94;
  float fVar95;
  undefined auVar90 [16];
  undefined auVar91 [16];
  undefined4 uVar96;
  float sc;
  float fVar97;
  float fVar98;
  float fVar99;
  float u;
  float fVar100;
  float fVar101;
  float fVar102;
  float fVar103;
  float fVar104;
  float fVar105;
  float fVar106;
  float v;
  float fVar107;
  float fVar108;
  float fVar109;
  float fVar110;
  float sigma;
  undefined auVar111 [16];
  undefined4 uVar115;
  float fVar116;
  float b;
  float fVar117;
  float edge;
  float a;
  undefined auVar118 [16];
  undefined auVar119 [16];
  undefined auVar121 [16];
  undefined auVar125 [16];
  float fVar126;
  float c;
  float fVar127;
  undefined auVar128 [12];
  undefined auVar130 [16];
  undefined auVar131 [16];
  undefined auVar133 [16];
  undefined auVar137 [16];
  undefined auVar138 [16];
  float fVar140;
  float fVar141;
  float fVar142;
  float fVar143;
  float fVar144;
  float fVar145;
  float fVar146;
  float fVar147;
  byte bVar148;
  byte bVar149;
  byte bVar150;
  byte bVar151;
  byte bVar152;
  byte bVar153;
  byte bVar154;
  byte bVar155;
  byte bVar156;
  float fVar157;
  undefined auVar159 [16];
  undefined auVar160 [16];
  undefined auVar164 [16];
  undefined auVar165 [16];
  float fVar167;
  float fVar168;
  float fVar169;
  float fVar170;
  byte bVar171;
  byte bVar172;
  byte bVar173;
  byte bVar174;
  byte bVar175;
  byte bVar176;
  byte bVar177;
  byte bVar178;
  byte bVar179;
  float fVar180;
  float fVar182;
  float fVar183;
  undefined auVar181 [16];
  float fVar184;
  byte bVar185;
  byte bVar186;
  byte bVar187;
  byte bVar188;
  byte bVar189;
  byte bVar190;
  byte bVar191;
  byte bVar192;
  byte bVar193;
  float fVar194;
  undefined auVar196 [16];
  undefined auVar197 [16];
  undefined auVar198 [16];
  undefined auVar200 [16];
  undefined auVar201 [16];
  undefined auVar202 [16];
  float fVar203;
  undefined auVar204 [16];
  undefined auVar205 [16];
  undefined auVar206 [16];
  float fVar207;
  float fVar208;
  u32 hist [256];
  float fStack_4d8;
  float fStack_4d4;
  undefined8 uStack_4b8;
  float local_4a0 [256];
  undefined auVar112 [16];
  undefined auVar113 [16];
  undefined auVar114 [16];
  undefined auVar122 [16];
  undefined auVar123 [16];
  undefined auVar120 [16];
  undefined auVar124 [16];
  undefined auVar134 [16];
  undefined auVar135 [16];
  undefined auVar129 [12];
  undefined auVar132 [16];
  undefined auVar136 [16];
  undefined auVar139 [16];
  undefined auVar161 [16];
  undefined auVar162 [16];
  undefined auVar158 [12];
  undefined auVar163 [16];
  undefined auVar166 [16];
  undefined auVar195 [12];
  undefined auVar199 [16];
  
  if (0x4000 < h) {
    return 0;
  }
  if (0x4000 < w) {
    return 0;
  }
  if (data == (u8 *)0x0) {
    return 0;
  }
  if (w < 2) {
    return 0;
  }
  if (h < 2) {
    return 0;
  }
  uVar43 = (ulong)(uint)stride;
  if (stride < w * 4) {
    return 0;
  }
  uVar42 = (ulong)(uint)w;
  lVar29 = uVar42 + (ulong)(uint)w * 2;
  out = (unkbyte9 *)malloc((ulong)(uint)w * 0xa8);
  __s = (unkbyte9 *)malloc(lVar29 * 8);
  iVar40 = 0;
  pVar22 = out;
  if ((out == (unkbyte9 *)0x0) || (__s == (unkbyte9 *)0x0)) goto LAB_001054ac;
  uVar27 = lVar29 * 2;
  memset(local_4a0,0,0x400);
  fVar110 = 1.0;
  if (3 < (uint)h) {
    puVar31 = data + uVar43 + 10;
    lVar32 = 8;
    if ((uint)(h * w) < 0xf42401) {
      lVar32 = 4;
    }
    uVar26 = 0;
    puVar36 = data + uVar43 * 2 + 5;
    uVar41 = 1;
    do {
      if (3 < (uint)w) {
        lVar23 = 0;
        uVar24 = 1;
        do {
          pbVar4 = puVar31 + lVar23;
          fVar86 = (float)NEON_ucvtf((uint)pbVar4[-5]);
          uVar96 = NEON_ucvtf((uint)pbVar4[-6]);
          uVar115 = NEON_ucvtf((uint)pbVar4[-4]);
          uVar96 = NEON_fmadd(uVar96,0x3e59b3d0,fVar86 * 0.7152);
          fVar86 = (float)NEON_fmadd(uVar115,0x3d93dd98,uVar96);
          if (8.0 <= fVar86 && fVar86 == 246.0 || 8.0 <= fVar86 && fVar86 < 246.0) {
            fVar103 = (float)NEON_ucvtf((uint)pbVar4[-1]);
            uVar96 = NEON_ucvtf((uint)pbVar4[-2]);
            uVar96 = NEON_fmadd(uVar96,0x3e59b3d0,fVar103 * 0.7152);
            uVar115 = NEON_ucvtf((uint)*pbVar4);
            fVar116 = (float)NEON_fmadd(uVar115,0x3d93dd98,uVar96);
            fVar104 = fVar86 - fVar116;
            fVar103 = -fVar104;
            if (0.0 <= fVar104) {
              fVar103 = fVar104;
            }
            if (fVar103 <= 12.0) {
              pbVar4 = puVar36 + lVar23;
              fVar103 = (float)NEON_ucvtf((uint)*pbVar4);
              uVar96 = NEON_ucvtf((uint)pbVar4[-1]);
              uVar96 = NEON_fmadd(uVar96,0x3e59b3d0,fVar103 * 0.7152);
              uVar115 = NEON_ucvtf((uint)pbVar4[1]);
              fVar126 = (float)NEON_fmadd(uVar115,0x3d93dd98,uVar96);
              fVar86 = fVar86 - fVar126;
              fVar103 = -fVar86;
              if (0.0 <= fVar86) {
                fVar103 = fVar86;
              }
              if (fVar103 <= 12.0) {
                fVar86 = (float)NEON_ucvtf((uint)pbVar4[4]);
                uVar96 = NEON_ucvtf((uint)pbVar4[3]);
                uVar96 = NEON_fmadd(uVar96,0x3e59b3d0,fVar86 * 0.7152);
                uVar115 = NEON_ucvtf((uint)pbVar4[5]);
                fVar103 = (float)NEON_fmadd(uVar115,0x3d93dd98,uVar96);
                fVar116 = fVar103 - fVar116;
                fVar86 = -fVar116;
                if (0.0 <= fVar116) {
                  fVar86 = fVar116;
                }
                if (fVar86 <= 12.0) {
                  fVar116 = fVar103 - fVar126;
                  fVar86 = -fVar116;
                  if (0.0 <= fVar116) {
                    fVar86 = fVar116;
                  }
                  if (fVar86 <= 12.0) {
                    uVar26 = uVar26 + 1;
                    fVar103 = (fVar104 - fVar126) + fVar103;
                    fVar86 = -fVar103;
                    if (0.0 <= fVar103) {
                      fVar86 = fVar103;
                    }
                    fVar86 = (float)NEON_fmadd(fVar86,0x40000000,0x3f000000);
                    uVar25 = (uint)fVar86;
                    if (0xfe < (int)uVar25) {
                      uVar25 = 0xff;
                    }
                    uVar25 = uVar25 & ((int)uVar25 >> 0x1f ^ 0xffffffffU);
                    local_4a0[uVar25] = (float)((int)local_4a0[uVar25] + 1);
                  }
                }
              }
            }
          }
          uVar24 = uVar24 + lVar32;
          lVar23 = lVar23 + lVar32 * 4;
        } while (uVar24 < w - 2);
      }
      uVar41 = uVar41 + lVar32;
      puVar31 = puVar31 + lVar32 * uVar43;
      puVar36 = puVar36 + lVar32 * uVar43;
    } while (uVar41 < h - 2);
    if (0x1f < uVar26) {
      lVar32 = 0;
      uVar25 = 0;
      do {
        uVar25 = (int)local_4a0[lVar32] + uVar25;
        if (uVar26 + 1 >> 1 <= uVar25) {
          fVar110 = (float)(int)lVar32;
          goto LAB_0010493c;
        }
        lVar32 = lVar32 + 1;
      } while (lVar32 != 0xff);
      fVar110 = 255.0;
LAB_0010493c:
      fVar86 = 7.0;
      if (fVar110 / 2.698 <= 7.0) {
        fVar86 = fVar110 / 2.698;
      }
      fVar110 = 0.7;
      if (0.7 <= fVar86) {
        fVar110 = fVar86;
      }
    }
  }
  bVar21 = finishing == 0;
  fVar86 = 0.88;
  if (!bVar21) {
    fVar86 = 0.4;
  }
  memset(__s,0,lVar29 * 8);
  horizontal(data,w,h,stride,-3,(float *)out);
  puVar5 = (undefined8 *)((long)out + lVar29 * 8);
  if (w == 0) {
    horizontal(data,0,h,stride,-2,(float *)puVar5);
LAB_00104aac:
    horizontal(data,w,h,stride,-1,(float *)(out + uVar42 * 3));
LAB_00104acc:
    horizontal(data,w,h,stride,0,(float *)((long)out + uVar42 * 0x48));
LAB_00104aec:
    horizontal(data,w,h,stride,1,(float *)(out + uVar42 * 6));
LAB_00104b0c:
    horizontal(data,w,h,stride,2,(float *)((long)out + uVar42 * 0x78));
LAB_00104b2c:
    horizontal(data,w,h,stride,3,(float *)(out + uVar42 * 9));
  }
  else {
    if (w == 1) {
      uVar24 = 0;
LAB_00104a4c:
      lVar32 = uVar24 + lVar29 * -2;
      pfVar34 = (float *)((long)__s + uVar24 * 4);
      pfVar35 = (float *)((long)out + uVar24 * 4);
      do {
        bVar20 = lVar32 != -1;
        lVar32 = lVar32 + 1;
        *pfVar34 = *pfVar35 + *pfVar34;
        pfVar34 = pfVar34 + 1;
        pfVar35 = pfVar35 + 1;
      } while (bVar20);
    }
    else {
      pauVar44 = (undefined (*) [16])(out + 1);
      uVar24 = uVar27 & 0x3fffffff8;
      pauVar33 = (undefined (*) [16])(__s + 1);
      uVar41 = uVar24;
      do {
        auVar118 = pauVar33[-1];
        auVar130 = *pauVar33;
        uVar41 = uVar41 - 8;
        auVar79 = pauVar44[-1];
        auVar197 = *pauVar44;
        pauVar44 = pauVar44 + 2;
        *(float *)*pauVar33 = auVar79._8_4_ + auVar118._8_4_;
        *(float *)((long)*pauVar33 + 4) = auVar79._12_4_ + auVar118._12_4_;
        *(float *)pauVar33[-1] = auVar79._0_4_ + auVar118._0_4_;
        *(float *)((long)pauVar33[-1] + 4) = auVar79._4_4_ + auVar118._4_4_;
        *(float *)pauVar33[1] = auVar197._8_4_ + auVar130._8_4_;
        *(float *)((long)pauVar33[1] + 4) = auVar197._12_4_ + auVar130._12_4_;
        *(float *)*pauVar33 = auVar197._0_4_ + auVar130._0_4_;
        *(float *)((long)*pauVar33 + 4) = auVar197._4_4_ + auVar130._4_4_;
        pauVar33 = pauVar33 + 2;
      } while (uVar41 != 0);
      if (uVar27 != uVar24) goto LAB_00104a4c;
    }
    horizontal(data,w,h,stride,-2,(float *)puVar5);
    if (w == 0) goto LAB_00104aac;
    if (w == 1) {
      uVar24 = 0;
LAB_0010553c:
      lVar32 = uVar24 + lVar29 * -2;
      pfVar34 = (float *)((long)__s + uVar24 * 4);
      pfVar35 = (float *)((long)out + uVar24 * 4 + uVar42 * 0x18);
      do {
        bVar20 = lVar32 != -1;
        lVar32 = lVar32 + 1;
        *pfVar34 = *pfVar35 + *pfVar34;
        pfVar34 = pfVar34 + 1;
        pfVar35 = pfVar35 + 1;
      } while (bVar20);
    }
    else {
      pauVar44 = (undefined (*) [16])(__s + 1);
      uVar24 = uVar27 & 0x3fffffff8;
      pauVar33 = (undefined (*) [16])((long)out + uVar42 * 0x18 + 0x10);
      uVar41 = uVar24;
      do {
        auVar118 = pauVar44[-1];
        auVar130 = *pauVar44;
        uVar41 = uVar41 - 8;
        auVar79 = pauVar33[-1];
        auVar197 = *pauVar33;
        pauVar33 = pauVar33 + 2;
        *(float *)*pauVar44 = auVar79._8_4_ + auVar118._8_4_;
        *(float *)((long)*pauVar44 + 4) = auVar79._12_4_ + auVar118._12_4_;
        *(float *)pauVar44[-1] = auVar79._0_4_ + auVar118._0_4_;
        *(float *)((long)pauVar44[-1] + 4) = auVar79._4_4_ + auVar118._4_4_;
        *(float *)pauVar44[1] = auVar197._8_4_ + auVar130._8_4_;
        *(float *)((long)pauVar44[1] + 4) = auVar197._12_4_ + auVar130._12_4_;
        *(float *)*pauVar44 = auVar197._0_4_ + auVar130._0_4_;
        *(float *)((long)*pauVar44 + 4) = auVar197._4_4_ + auVar130._4_4_;
        pauVar44 = pauVar44 + 2;
      } while (uVar41 != 0);
      if (uVar27 != uVar24) goto LAB_0010553c;
    }
    horizontal(data,w,h,stride,-1,(float *)(out + uVar42 * 3));
    if (w == 0) goto LAB_00104acc;
    if (w == 1) {
      uVar24 = 0;
LAB_001055f8:
      lVar32 = uVar24 + lVar29 * -2;
      pfVar34 = (float *)((long)__s + uVar24 * 4);
      pfVar35 = (float *)((long)out + uVar24 * 4 + uVar42 * 0x30);
      do {
        bVar20 = lVar32 != -1;
        lVar32 = lVar32 + 1;
        *pfVar34 = *pfVar35 + *pfVar34;
        pfVar34 = pfVar34 + 1;
        pfVar35 = pfVar35 + 1;
      } while (bVar20);
    }
    else {
      pauVar44 = (undefined (*) [16])(__s + 1);
      uVar24 = uVar27 & 0x3fffffff8;
      pauVar33 = (undefined (*) [16])(out + uVar42 * 3 + 1);
      uVar41 = uVar24;
      do {
        auVar118 = pauVar44[-1];
        auVar130 = *pauVar44;
        uVar41 = uVar41 - 8;
        auVar79 = pauVar33[-1];
        auVar197 = *pauVar33;
        pauVar33 = pauVar33 + 2;
        *(float *)*pauVar44 = auVar79._8_4_ + auVar118._8_4_;
        *(float *)((long)*pauVar44 + 4) = auVar79._12_4_ + auVar118._12_4_;
        *(float *)pauVar44[-1] = auVar79._0_4_ + auVar118._0_4_;
        *(float *)((long)pauVar44[-1] + 4) = auVar79._4_4_ + auVar118._4_4_;
        *(float *)pauVar44[1] = auVar197._8_4_ + auVar130._8_4_;
        *(float *)((long)pauVar44[1] + 4) = auVar197._12_4_ + auVar130._12_4_;
        *(float *)*pauVar44 = auVar197._0_4_ + auVar130._0_4_;
        *(float *)((long)*pauVar44 + 4) = auVar197._4_4_ + auVar130._4_4_;
        pauVar44 = pauVar44 + 2;
      } while (uVar41 != 0);
      if (uVar27 != uVar24) goto LAB_001055f8;
    }
    horizontal(data,w,h,stride,0,(float *)((long)out + uVar42 * 0x48));
    if (w == 0) goto LAB_00104aec;
    if (w == 1) {
      uVar24 = 0;
LAB_001056b4:
      lVar32 = uVar24 + lVar29 * -2;
      pfVar34 = (float *)((long)__s + uVar24 * 4);
      pfVar35 = (float *)((long)out + uVar24 * 4 + uVar42 * 0x48);
      do {
        bVar20 = lVar32 != -1;
        lVar32 = lVar32 + 1;
        *pfVar34 = *pfVar35 + *pfVar34;
        pfVar34 = pfVar34 + 1;
        pfVar35 = pfVar35 + 1;
      } while (bVar20);
    }
    else {
      pauVar44 = (undefined (*) [16])(__s + 1);
      uVar24 = uVar27 & 0x3fffffff8;
      pauVar33 = (undefined (*) [16])((long)out + uVar42 * 0x48 + 0x10);
      uVar41 = uVar24;
      do {
        auVar118 = pauVar44[-1];
        auVar130 = *pauVar44;
        uVar41 = uVar41 - 8;
        auVar79 = pauVar33[-1];
        auVar197 = *pauVar33;
        pauVar33 = pauVar33 + 2;
        *(float *)*pauVar44 = auVar79._8_4_ + auVar118._8_4_;
        *(float *)((long)*pauVar44 + 4) = auVar79._12_4_ + auVar118._12_4_;
        *(float *)pauVar44[-1] = auVar79._0_4_ + auVar118._0_4_;
        *(float *)((long)pauVar44[-1] + 4) = auVar79._4_4_ + auVar118._4_4_;
        *(float *)pauVar44[1] = auVar197._8_4_ + auVar130._8_4_;
        *(float *)((long)pauVar44[1] + 4) = auVar197._12_4_ + auVar130._12_4_;
        *(float *)*pauVar44 = auVar197._0_4_ + auVar130._0_4_;
        *(float *)((long)*pauVar44 + 4) = auVar197._4_4_ + auVar130._4_4_;
        pauVar44 = pauVar44 + 2;
      } while (uVar41 != 0);
      if (uVar27 != uVar24) goto LAB_001056b4;
    }
    horizontal(data,w,h,stride,1,(float *)(out + uVar42 * 6));
    if (w == 0) goto LAB_00104b0c;
    if (w == 1) {
      uVar24 = 0;
LAB_00105770:
      lVar32 = uVar24 + lVar29 * -2;
      pfVar34 = (float *)((long)__s + uVar24 * 4);
      pfVar35 = (float *)((long)out + uVar24 * 4 + uVar42 * 0x60);
      do {
        bVar20 = lVar32 != -1;
        lVar32 = lVar32 + 1;
        *pfVar34 = *pfVar35 + *pfVar34;
        pfVar34 = pfVar34 + 1;
        pfVar35 = pfVar35 + 1;
      } while (bVar20);
    }
    else {
      pauVar44 = (undefined (*) [16])(__s + 1);
      uVar24 = uVar27 & 0x3fffffff8;
      pauVar33 = (undefined (*) [16])(out + uVar42 * 6 + 1);
      uVar41 = uVar24;
      do {
        auVar118 = pauVar44[-1];
        auVar130 = *pauVar44;
        uVar41 = uVar41 - 8;
        auVar79 = pauVar33[-1];
        auVar197 = *pauVar33;
        pauVar33 = pauVar33 + 2;
        *(float *)*pauVar44 = auVar79._8_4_ + auVar118._8_4_;
        *(float *)((long)*pauVar44 + 4) = auVar79._12_4_ + auVar118._12_4_;
        *(float *)pauVar44[-1] = auVar79._0_4_ + auVar118._0_4_;
        *(float *)((long)pauVar44[-1] + 4) = auVar79._4_4_ + auVar118._4_4_;
        *(float *)pauVar44[1] = auVar197._8_4_ + auVar130._8_4_;
        *(float *)((long)pauVar44[1] + 4) = auVar197._12_4_ + auVar130._12_4_;
        *(float *)*pauVar44 = auVar197._0_4_ + auVar130._0_4_;
        *(float *)((long)*pauVar44 + 4) = auVar197._4_4_ + auVar130._4_4_;
        pauVar44 = pauVar44 + 2;
      } while (uVar41 != 0);
      if (uVar27 != uVar24) goto LAB_00105770;
    }
    horizontal(data,w,h,stride,2,(float *)((long)out + uVar42 * 0x78));
    if (w == 0) goto LAB_00104b2c;
    if (w == 1) {
      uVar24 = 0;
LAB_0010582c:
      lVar32 = uVar24 + lVar29 * -2;
      pfVar34 = (float *)((long)__s + uVar24 * 4);
      pfVar35 = (float *)((long)out + uVar24 * 4 + uVar42 * 0x78);
      do {
        bVar20 = lVar32 != -1;
        lVar32 = lVar32 + 1;
        *pfVar34 = *pfVar35 + *pfVar34;
        pfVar34 = pfVar34 + 1;
        pfVar35 = pfVar35 + 1;
      } while (bVar20);
    }
    else {
      pauVar44 = (undefined (*) [16])(__s + 1);
      uVar24 = uVar27 & 0x3fffffff8;
      pauVar33 = (undefined (*) [16])((long)out + uVar42 * 0x78 + 0x10);
      uVar41 = uVar24;
      do {
        auVar118 = pauVar44[-1];
        auVar130 = *pauVar44;
        uVar41 = uVar41 - 8;
        auVar79 = pauVar33[-1];
        auVar197 = *pauVar33;
        pauVar33 = pauVar33 + 2;
        *(float *)*pauVar44 = auVar79._8_4_ + auVar118._8_4_;
        *(float *)((long)*pauVar44 + 4) = auVar79._12_4_ + auVar118._12_4_;
        *(float *)pauVar44[-1] = auVar79._0_4_ + auVar118._0_4_;
        *(float *)((long)pauVar44[-1] + 4) = auVar79._4_4_ + auVar118._4_4_;
        *(float *)pauVar44[1] = auVar197._8_4_ + auVar130._8_4_;
        *(float *)((long)pauVar44[1] + 4) = auVar197._12_4_ + auVar130._12_4_;
        *(float *)*pauVar44 = auVar197._0_4_ + auVar130._0_4_;
        *(float *)((long)*pauVar44 + 4) = auVar197._4_4_ + auVar130._4_4_;
        pauVar44 = pauVar44 + 2;
      } while (uVar41 != 0);
      if (uVar27 != uVar24) goto LAB_0010582c;
    }
    horizontal(data,w,h,stride,3,(float *)(out + uVar42 * 9));
    if (w != 0) {
      if (w == 1) {
        uVar24 = 0;
      }
      else {
        pauVar44 = (undefined (*) [16])(__s + 1);
        uVar24 = uVar27 & 0x3fffffff8;
        pauVar33 = (undefined (*) [16])(out + uVar42 * 9 + 1);
        uVar41 = uVar24;
        do {
          auVar118 = pauVar44[-1];
          auVar130 = *pauVar44;
          uVar41 = uVar41 - 8;
          auVar79 = pauVar33[-1];
          auVar197 = *pauVar33;
          pauVar33 = pauVar33 + 2;
          *(float *)*pauVar44 = auVar79._8_4_ + auVar118._8_4_;
          *(float *)((long)*pauVar44 + 4) = auVar79._12_4_ + auVar118._12_4_;
          *(float *)pauVar44[-1] = auVar79._0_4_ + auVar118._0_4_;
          *(float *)((long)pauVar44[-1] + 4) = auVar79._4_4_ + auVar118._4_4_;
          *(float *)pauVar44[1] = auVar197._8_4_ + auVar130._8_4_;
          *(float *)((long)pauVar44[1] + 4) = auVar197._12_4_ + auVar130._12_4_;
          *(float *)*pauVar44 = auVar197._0_4_ + auVar130._0_4_;
          *(float *)((long)*pauVar44 + 4) = auVar197._4_4_ + auVar130._4_4_;
          pauVar44 = pauVar44 + 2;
        } while (uVar41 != 0);
        if (uVar27 == uVar24) goto LAB_00104b50;
      }
      lVar29 = uVar24 + lVar29 * -2;
      pfVar34 = (float *)((long)__s + uVar24 * 4);
      pfVar35 = (float *)((long)out + uVar24 * 4 + uVar42 * 0x90);
      do {
        bVar20 = lVar29 != -1;
        lVar29 = lVar29 + 1;
        *pfVar34 = *pfVar35 + *pfVar34;
        pfVar34 = pfVar34 + 1;
        pfVar35 = pfVar35 + 1;
      } while (bVar20);
    }
  }
LAB_00104b50:
  if (0 < h) {
    fVar110 = fVar110 * fVar110;
    sc = 0.95;
    if (finishing != 0) {
      sc = 0.65;
    }
    uVar66 = NEON_cmlt(CONCAT44((uint)bVar21 << 0x1f,(uint)bVar21 << 0x1f),0,4);
    uVar24 = uVar27 & 0x3fffffff8;
    fVar103 = (float)NEON_fmadd(fVar110,0x41100000,0x40800000);
    uVar66 = NEON_bsl(uVar66,DAT_001004d8,DAT_001004d0,1);
    auVar130._0_4_ = (float)uVar66 * fVar110;
    auVar130._4_4_ = (float)((ulong)uVar66 >> 0x20) * fVar110;
    auVar118 = ZEXT816(0x3f0000003f000000);
    fVar86 = fVar86 * auVar130._0_4_;
    fVar110 = sc * auVar130._4_4_;
    uVar41 = 8;
    if ((w & 7U) != 0) {
      uVar41 = uVar42 & 7;
    }
    uVar28 = 0;
    local_4a0[0] = fVar103;
    local_4a0[1] = fVar103;
    do {
      auVar130._8_8_ = 0;
      if (0 < w) {
        if ((uint)w < 9 || uVar42 - 0x40000001 < 0xffffffffc0000000) {
          lVar29 = 0;
        }
        else {
          uVar37 = 0;
          lVar29 = uVar42 - uVar41;
          pVar22 = __s;
          auVar79 = auVar130;
          do {
            auVar48 = _DAT_001004e0;
            auVar125 = *(undefined (*) [16])(pVar22 + 3);
            auVar197 = *(undefined (*) [16])(pVar22 + 4);
            uVar9 = *(undefined8 *)((long)pVar22 + 8);
            uVar66 = *(undefined8 *)pVar22;
            Var18 = *pVar22;
            auVar204 = *(undefined (*) [16])(pVar22 + 1);
            auVar198 = *(undefined (*) [16])(pVar22 + 9);
            auVar202 = *(undefined (*) [16])(pVar22 + 10);
            puVar31 = data + (uVar37 & 0xffffffe0) + uVar28 * uVar43;
            auVar80 = *(undefined (*) [16])(pVar22 + 6);
            pVar6 = pVar22 + 7;
            uVar12 = *(undefined8 *)((long)pVar22 + 0x78);
            uVar11 = *(undefined8 *)pVar6;
            auVar164 = *(undefined (*) [16])(pVar22 + 2);
            auVar7 = *(undefined (*) [16])(pVar22 + 5);
            pauVar1 = (undefined (*) [12])(pVar22 + 8);
            puVar5 = (undefined8 *)((long)pVar22 + 0x88);
            auVar8 = *(undefined (*) [16])(pVar22 + 0xb);
            auVar200._8_8_ = auVar80._8_8_;
            fVar52 = auVar197._8_4_;
            auVar16._4_8_ = auVar79._8_8_;
            auVar16._0_4_ = fVar52;
            auVar128._0_8_ = auVar16._0_8_ << 0x20;
            fVar63 = auVar197._0_4_;
            auVar128._8_4_ = fVar63;
            auVar159._12_4_ = auVar197._12_4_;
            auVar159._8_4_ = auVar125._4_4_;
            auVar159._0_8_ = auVar197._0_8_;
            fVar104 = auVar164._4_4_;
            auVar111._4_12_ = auVar118._4_12_;
            auVar111._0_4_ = fVar104;
            auVar113._12_4_ = auVar118._12_4_;
            auVar113._0_8_ = auVar111._0_8_;
            auVar113._8_4_ = auVar164._12_4_;
            uVar96 = auVar204._4_4_;
            auVar112._8_8_ = auVar113._8_8_;
            auVar112._4_4_ = uVar96;
            auVar112._0_4_ = fVar104;
            auVar114._0_12_ = auVar112._0_12_;
            auVar114._12_4_ = auVar204._12_4_;
            auVar131._0_8_ = auVar128._4_8_ << 0x20;
            auVar131._8_4_ = fVar63;
            auVar131._12_4_ = fVar52;
            auVar17._4_8_ = auVar131._8_8_;
            auVar17._0_4_ = auVar7._0_4_;
            auVar132._0_12_ = auVar17 << 0x20;
            fVar64 = auVar7._8_4_;
            auVar132._12_4_ = fVar64;
            lVar29 = lVar29 + -8;
            uVar37 = uVar37 + 0x20;
            pVar22 = pVar22 + 0xc;
            fVar45 = (float)uVar66 / 49.0;
            fVar50 = auVar204._8_4_ / 49.0;
            fVar51 = auVar125._0_4_ / 49.0;
            fVar52 = fVar52 / 49.0;
            fVar65 = auVar80._0_4_ / 49.0;
            fVar72 = (float)uVar12 / 49.0;
            fVar74 = auVar198._0_4_ / 49.0;
            fVar76 = auVar202._8_4_ / 49.0;
            fVar53 = (float)uVar9 / 49.0;
            fVar57 = auVar164._0_4_ / 49.0;
            fVar58 = auVar125._8_4_ / 49.0;
            fVar59 = auVar7._0_4_ / 49.0;
            fVar105 = auVar80._8_4_ / 49.0;
            fVar107 = SUB124(*pauVar1,0) / 49.0;
            fVar108 = auVar198._8_4_ / 49.0;
            fVar109 = auVar8._0_4_ / 49.0;
            fVar97 = (float)uVar11 / 49.0;
            fVar100 = (float)*puVar5 / 49.0;
            fVar101 = auVar202._0_4_ / 49.0;
            fVar102 = auVar8._8_4_ / 49.0;
            auVar133._4_12_ = auVar132._4_12_;
            auVar133._0_4_ = uVar96;
            auVar135._0_8_ = auVar133._0_8_;
            auVar135._8_4_ = auVar204._12_4_;
            auVar135._12_4_ = fVar64;
            auVar134._8_8_ = auVar135._8_8_;
            auVar134._4_4_ = (int)((ulong)uVar66 >> 0x20);
            auVar134._0_4_ = uVar96;
            fVar116 = (float)((ulong)uVar9 >> 0x20);
            auVar136._0_12_ = auVar134._0_12_;
            auVar136._12_4_ = fVar116;
            auVar79 = NEON_ext(auVar114,auVar204,4,1);
            auVar196[9] = (char)((ulong)uVar9 >> 8);
            auVar196._0_9_ = Var18;
            auVar196[10] = (char)((ulong)uVar9 >> 0x10);
            auVar196[11] = (char)((ulong)uVar9 >> 0x18);
            auVar196[12] = (char)((ulong)uVar9 >> 0x20);
            auVar196[13] = (char)((ulong)uVar9 >> 0x28);
            auVar196[14] = (char)((ulong)uVar9 >> 0x30);
            auVar196[15] = (char)((ulong)uVar9 >> 0x38);
            auVar137 = NEON_ext(auVar136,auVar196,4,1);
            fVar60 = auVar204._0_4_ / 49.0;
            fVar62 = auVar164._8_4_ / 49.0;
            fVar63 = fVar63 / 49.0;
            fVar64 = fVar64 / 49.0;
            uVar96 = (undefined4)((ulong)uVar11 >> 0x20);
            auVar160._4_12_ = auVar159._4_12_;
            auVar160._0_4_ = uVar96;
            uVar115 = (undefined4)((ulong)uVar12 >> 0x20);
            auVar162._0_8_ = auVar160._0_8_;
            auVar162._8_4_ = uVar115;
            auVar162._12_4_ = auVar159._12_4_;
            auVar161._8_8_ = auVar162._8_8_;
            auVar161._4_4_ = auVar80._4_4_;
            auVar161._0_4_ = uVar96;
            auVar163._0_12_ = auVar161._0_12_;
            auVar163._12_4_ = auVar80._12_4_;
            auVar164 = NEON_ext(auVar163,auVar80,4,1);
            auVar204 = NEON_ext(auVar125,auVar7,8,1);
            fVar126 = auVar125._12_4_;
            fVar83 = auVar204._12_4_;
            auVar118 = NEON_ext(auVar198,auVar8,8,1);
            auVar138._0_4_ = auVar137._0_4_ / 49.0 - fVar45 * fVar45;
            auVar138._4_4_ = auVar137._4_4_ / 49.0 - fVar50 * fVar50;
            auVar138._8_4_ = auVar125._4_4_ / 49.0 - fVar51 * fVar51;
            auVar138._12_4_ = auVar159._12_4_ / 49.0 - fVar52 * fVar52;
            auVar119._0_8_ = auVar118._4_8_ << 0x20;
            auVar119._12_4_ = auVar118._12_4_;
            auVar119._8_4_ = auVar198._12_4_;
            auVar19._4_8_ = auVar119._8_8_;
            auVar19._0_4_ = auVar118._8_4_;
            auVar120._0_12_ = auVar19 << 0x20;
            auVar120._12_4_ = auVar119._12_4_;
            auVar121._4_12_ = auVar120._4_12_;
            auVar121._0_4_ = SUB124(*pauVar1,4);
            auVar123._0_8_ = auVar121._0_8_;
            auVar123._8_4_ = (int)((ulong)*puVar5 >> 0x20);
            auVar123._12_4_ = auVar119._12_4_;
            auVar122._8_8_ = auVar123._8_8_;
            auVar122._4_4_ = uVar96;
            auVar122._0_4_ = SUB124(*pauVar1,4);
            auVar124._0_12_ = auVar122._0_12_;
            auVar124._12_4_ = uVar115;
            auVar181._8_4_ = _UNK_00100508;
            auVar181._0_8_ = _DAT_00100500;
            auVar137._8_4_ = _UNK_00100508;
            auVar137._0_8_ = _DAT_00100500;
            auVar118._8_4_ = _UNK_00100508;
            auVar118._0_8_ = _DAT_00100500;
            auVar200[0] = *puVar31;
            auVar205[0] = puVar31[1];
            auVar200[1] = puVar31[4];
            auVar205[1] = puVar31[5];
            auVar200[2] = puVar31[8];
            auVar205[2] = puVar31[9];
            auVar200[3] = puVar31[0xc];
            auVar205[3] = puVar31[0xd];
            auVar200[4] = puVar31[0x10];
            auVar205[4] = puVar31[0x11];
            auVar200[5] = puVar31[0x14];
            auVar205[5] = puVar31[0x15];
            auVar200[6] = puVar31[0x18];
            auVar205[6] = puVar31[0x19];
            auVar200[7] = puVar31[0x1c];
            auVar205._8_8_ = auVar204._8_8_;
            auVar205[7] = puVar31[0x1d];
            auVar201[9] = (char)((ulong)uVar12 >> 8);
            auVar201._0_9_ = *pVar6;
            auVar201[10] = (char)((ulong)uVar12 >> 0x10);
            auVar201[11] = (char)((ulong)uVar12 >> 0x18);
            auVar201[12] = (char)((ulong)uVar12 >> 0x20);
            auVar201[13] = (char)((ulong)uVar12 >> 0x28);
            auVar201[14] = (char)((ulong)uVar12 >> 0x30);
            auVar201[15] = (char)((ulong)uVar12 >> 0x38);
            auVar204 = NEON_ext(auVar124,auVar201,4,1);
            auVar165._0_4_ = auVar164._0_4_ / 49.0 - fVar65 * fVar65;
            auVar165._4_4_ = auVar164._4_4_ / 49.0 - fVar72 * fVar72;
            auVar165._8_4_ = auVar198._4_4_ / 49.0 - fVar74 * fVar74;
            auVar165._12_4_ = auVar202._12_4_ / 49.0 - fVar76 * fVar76;
            auVar118._12_4_ = _UNK_0010050c;
            auVar125 = a64_TBL(ZEXT816(0),auVar205,auVar118);
            auVar137._12_4_ = _UNK_0010050c;
            auVar137 = a64_TBL(ZEXT816(0),auVar200,auVar137);
            auVar118 = a64_TBL(ZEXT816(0),auVar205,_DAT_001004f0);
            auVar164 = a64_TBL(ZEXT816(0),auVar200,_DAT_001004f0);
            auVar14[1] = puVar31[6];
            auVar14[0] = puVar31[2];
            auVar14[2] = puVar31[10];
            auVar14[3] = puVar31[0xe];
            auVar14[4] = puVar31[0x12];
            auVar14[5] = puVar31[0x16];
            auVar14[6] = puVar31[0x1a];
            auVar14[7] = puVar31[0x1e];
            auVar14._8_4_ = fVar126;
            auVar14._12_4_ = fVar83;
            auVar201 = a64_TBL(ZEXT816(0),auVar14,_DAT_001004f0);
            auVar196 = NEON_ucvtf(auVar125,4);
            auVar137 = NEON_ucvtf(auVar137,4);
            auVar181._12_4_ = _UNK_0010050c;
            auVar15[1] = puVar31[6];
            auVar15[0] = puVar31[2];
            auVar15[2] = puVar31[10];
            auVar15[3] = puVar31[0xe];
            auVar15[4] = puVar31[0x12];
            auVar15[5] = puVar31[0x16];
            auVar15[6] = puVar31[0x1a];
            auVar15[7] = puVar31[0x1e];
            auVar15._8_4_ = fVar126;
            auVar15._12_4_ = fVar83;
            auVar181 = a64_TBL(ZEXT816(0),auVar15,auVar181);
            auVar118 = NEON_ucvtf(auVar118,4);
            auVar125 = NEON_ucvtf(auVar164,4);
            fVar116 = fVar116 / 49.0 - fVar53 * fVar53;
            fVar104 = fVar104 / 49.0 - fVar57 * fVar57;
            bVar148 = (byte)((uint)fVar104 >> 8);
            bVar149 = (byte)((uint)fVar104 >> 0x10);
            bVar150 = (byte)((uint)fVar104 >> 0x18);
            fVar126 = fVar126 / 49.0 - fVar58 * fVar58;
            bVar151 = (byte)((uint)fVar126 >> 8);
            bVar152 = (byte)((uint)fVar126 >> 0x10);
            bVar153 = (byte)((uint)fVar126 >> 0x18);
            fVar83 = fVar83 / 49.0 - fVar59 * fVar59;
            bVar154 = (byte)((uint)fVar83 >> 8);
            bVar155 = (byte)((uint)fVar83 >> 0x10);
            bVar156 = (byte)((uint)fVar83 >> 0x18);
            auVar164 = NEON_ucvtf(auVar181,4);
            fVar140 = auVar196._0_4_ * 0.7152 + auVar137._0_4_ * 0.2126 + auVar164._0_4_ * 0.0722;
            fVar141 = auVar196._4_4_ * 0.7152 + auVar137._4_4_ * 0.2126 + auVar164._4_4_ * 0.0722;
            fVar142 = auVar196._8_4_ * 0.7152 + auVar137._8_4_ * 0.2126 + auVar164._8_4_ * 0.0722;
            fVar143 = auVar196._12_4_ * 0.7152 + auVar137._12_4_ * 0.2126 + auVar164._12_4_ * 0.0722
            ;
            fVar89 = auVar204._0_4_ / 49.0 - fVar97 * fVar97;
            fVar98 = auVar204._4_4_ / 49.0 - fVar100 * fVar100;
            bVar171 = (byte)((uint)fVar98 >> 8);
            bVar172 = (byte)((uint)fVar98 >> 0x10);
            bVar173 = (byte)((uint)fVar98 >> 0x18);
            fVar99 = auVar202._4_4_ / 49.0 - fVar101 * fVar101;
            bVar174 = (byte)((uint)fVar99 >> 8);
            bVar175 = (byte)((uint)fVar99 >> 0x10);
            bVar176 = (byte)((uint)fVar99 >> 0x18);
            fVar106 = auVar8._12_4_ / 49.0 - fVar102 * fVar102;
            bVar177 = (byte)((uint)fVar106 >> 8);
            bVar178 = (byte)((uint)fVar106 >> 0x10);
            bVar179 = (byte)((uint)fVar106 >> 0x18);
            fVar167 = auVar137._0_4_ - fVar140;
            fVar168 = auVar137._4_4_ - fVar141;
            fVar169 = auVar137._8_4_ - fVar142;
            fVar170 = auVar137._12_4_ - fVar143;
            fVar180 = auVar164._0_4_ - fVar140;
            fVar182 = auVar164._4_4_ - fVar141;
            fVar183 = auVar164._8_4_ - fVar142;
            fVar184 = auVar164._12_4_ - fVar143;
            auVar204 = NEON_ucvtf(auVar201,4);
            auVar202 = NEON_fmov(0x3f800000,4);
            auVar206._0_4_ = auVar79._0_4_ / 49.0 - fVar60 * fVar60;
            auVar206._4_4_ = auVar79._4_4_ / 49.0 - fVar62 * fVar62;
            auVar206._8_4_ = auVar197._4_4_ / 49.0 - fVar63 * fVar63;
            auVar206._12_4_ = auVar7._12_4_ / 49.0 - fVar64 * fVar64;
            fVar78 = auVar118._0_4_ * 0.7152 + auVar125._0_4_ * 0.2126 + auVar204._0_4_ * 0.0722;
            fVar82 = auVar118._4_4_ * 0.7152 + auVar125._4_4_ * 0.2126 + auVar204._4_4_ * 0.0722;
            fVar84 = auVar118._8_4_ * 0.7152 + auVar125._8_4_ * 0.2126 + auVar204._8_4_ * 0.0722;
            fVar85 = auVar118._12_4_ * 0.7152 + auVar125._12_4_ * 0.2126 + auVar204._12_4_ * 0.0722;
            fVar87 = auVar125._0_4_ - fVar78;
            fVar92 = auVar125._4_4_ - fVar82;
            fVar94 = auVar125._8_4_ - fVar84;
            fVar95 = auVar125._12_4_ - fVar85;
            fVar117 = auVar80._12_4_ / 49.0 - fVar105 * fVar105;
            fVar73 = (float)((ulong)*(undefined8 *)*pauVar1 >> 0x20) / 49.0 - fVar107 * fVar107;
            bVar185 = (byte)((uint)fVar73 >> 8);
            bVar186 = (byte)((uint)fVar73 >> 0x10);
            bVar187 = (byte)((uint)fVar73 >> 0x18);
            fVar75 = auVar198._12_4_ / 49.0 - fVar108 * fVar108;
            bVar188 = (byte)((uint)fVar75 >> 8);
            bVar189 = (byte)((uint)fVar75 >> 0x10);
            bVar190 = (byte)((uint)fVar75 >> 0x18);
            fVar77 = auVar119._12_4_ / 49.0 - fVar109 * fVar109;
            bVar191 = (byte)((uint)fVar77 >> 8);
            bVar192 = (byte)((uint)fVar77 >> 0x10);
            bVar193 = (byte)((uint)fVar77 >> 0x18);
            fVar144 = auVar202._0_4_;
            fVar145 = auVar202._4_4_;
            fVar146 = auVar202._8_4_;
            fVar147 = auVar202._12_4_;
            fVar88 = fVar144 / (((fVar140 - fVar65) * (fVar140 - fVar65)) / fVar103 + fVar144);
            fVar93 = fVar145 / (((fVar141 - fVar72) * (fVar141 - fVar72)) / fVar103 + fVar145);
            fVar207 = fVar146 / (((fVar142 - fVar74) * (fVar142 - fVar74)) / 0.0 + fVar146);
            fVar208 = fVar147 / (((fVar143 - fVar76) * (fVar143 - fVar76)) / 0.0 + fVar147);
            auVar79 = NEON_fcmlt(auVar165,0,4);
            fVar157 = (float)CONCAT13((byte)((uint)auVar165._0_4_ >> 0x18) & ~auVar79[3],
                                      CONCAT12((byte)((uint)auVar165._0_4_ >> 0x10) & ~auVar79[2],
                                               CONCAT11((byte)((uint)auVar165._0_4_ >> 8) &
                                                        ~auVar79[1],
                                                        SUB41(auVar165._0_4_,0) & ~auVar79[0])));
            auVar158._0_8_ =
                 CONCAT17((byte)((uint)auVar165._4_4_ >> 0x18) & ~auVar79[7],
                          CONCAT16((byte)((uint)auVar165._4_4_ >> 0x10) & ~auVar79[6],
                                   CONCAT15((byte)((uint)auVar165._4_4_ >> 8) & ~auVar79[5],
                                            CONCAT14(SUB41(auVar165._4_4_,0) & ~auVar79[4],fVar157))
                                  ));
            auVar158[8] = SUB41(auVar165._8_4_,0) & ~auVar79[8];
            auVar158[9] = (byte)((uint)auVar165._8_4_ >> 8) & ~auVar79[9];
            auVar158[10] = (byte)((uint)auVar165._8_4_ >> 0x10) & ~auVar79[10];
            auVar158[11] = (byte)((uint)auVar165._8_4_ >> 0x18) & ~auVar79[11];
            auVar166[12] = SUB41(auVar165._12_4_,0) & ~auVar79[12];
            auVar166._0_12_ = auVar158;
            auVar166[13] = (byte)((uint)auVar165._12_4_ >> 8) & ~auVar79[13];
            auVar166[14] = (byte)((uint)auVar165._12_4_ >> 0x10) & ~auVar79[14];
            auVar166[15] = (byte)((uint)auVar165._12_4_ >> 0x18) & ~auVar79[15];
            auVar79 = NEON_fcmlt(auVar138,0,4);
            fVar144 = fVar144 / (((fVar78 - fVar45) * (fVar78 - fVar45)) / fVar103 + fVar144);
            fVar145 = fVar145 / (((fVar82 - fVar50) * (fVar82 - fVar50)) / fVar103 + fVar145);
            fVar146 = fVar146 / (((fVar84 - fVar51) * (fVar84 - fVar51)) / 0.0 + fVar146);
            fVar147 = fVar147 / (((fVar85 - fVar52) * (fVar85 - fVar52)) / 0.0 + fVar147);
            fVar127 = (float)CONCAT13((byte)((uint)auVar138._0_4_ >> 0x18) & ~auVar79[3],
                                      CONCAT12((byte)((uint)auVar138._0_4_ >> 0x10) & ~auVar79[2],
                                               CONCAT11((byte)((uint)auVar138._0_4_ >> 8) &
                                                        ~auVar79[1],
                                                        SUB41(auVar138._0_4_,0) & ~auVar79[0])));
            auVar129._0_8_ =
                 CONCAT17((byte)((uint)auVar138._4_4_ >> 0x18) & ~auVar79[7],
                          CONCAT16((byte)((uint)auVar138._4_4_ >> 0x10) & ~auVar79[6],
                                   CONCAT15((byte)((uint)auVar138._4_4_ >> 8) & ~auVar79[5],
                                            CONCAT14(SUB41(auVar138._4_4_,0) & ~auVar79[4],fVar127))
                                  ));
            auVar129[8] = SUB41(auVar138._8_4_,0) & ~auVar79[8];
            auVar129[9] = (byte)((uint)auVar138._8_4_ >> 8) & ~auVar79[9];
            auVar129[10] = (byte)((uint)auVar138._8_4_ >> 0x10) & ~auVar79[10];
            auVar129[11] = (byte)((uint)auVar138._8_4_ >> 0x18) & ~auVar79[11];
            auVar139[12] = SUB41(auVar138._12_4_,0) & ~auVar79[12];
            auVar139._0_12_ = auVar129;
            auVar139[13] = (byte)((uint)auVar138._12_4_ >> 8) & ~auVar79[13];
            auVar139[14] = (byte)((uint)auVar138._12_4_ >> 0x10) & ~auVar79[14];
            auVar139[15] = (byte)((uint)auVar138._12_4_ >> 0x18) & ~auVar79[15];
            auVar13[4] = SUB41(fVar73,0);
            auVar13._0_4_ = fVar117;
            auVar13[5] = bVar185;
            auVar13[6] = bVar186;
            auVar13[7] = bVar187;
            auVar13[8] = SUB41(fVar75,0);
            auVar13[9] = bVar188;
            auVar13[10] = bVar189;
            auVar13[11] = bVar190;
            auVar13[12] = SUB41(fVar77,0);
            auVar13[13] = bVar191;
            auVar13[14] = bVar192;
            auVar13[15] = bVar193;
            auVar197 = NEON_fcmlt(auVar13,0,4);
            fVar203 = (float)((ulong)uStack_4b8 >> 0x20);
            auVar8[4] = SUB41(fVar104,0);
            auVar8._0_4_ = fVar116;
            auVar8[5] = bVar148;
            auVar8[6] = bVar149;
            auVar8[7] = bVar150;
            auVar8[8] = SUB41(fVar126,0);
            auVar8[9] = bVar151;
            auVar8[10] = bVar152;
            auVar8[11] = bVar153;
            auVar8[12] = SUB41(fVar83,0);
            auVar8[13] = bVar154;
            auVar8[14] = bVar155;
            auVar8[15] = bVar156;
            auVar125 = NEON_fcmlt(auVar8,0,4);
            auVar10[4] = SUB41(fVar98,0);
            auVar10._0_4_ = fVar89;
            auVar10[5] = bVar171;
            auVar10[6] = bVar172;
            auVar10[7] = bVar173;
            auVar10[8] = SUB41(fVar99,0);
            auVar10[9] = bVar174;
            auVar10[10] = bVar175;
            auVar10[11] = bVar176;
            auVar10[12] = SUB41(fVar106,0);
            auVar10[13] = bVar177;
            auVar10[14] = bVar178;
            auVar10[15] = bVar179;
            auVar198 = NEON_fcmlt(auVar10,0,4);
            auVar79 = NEON_fcmlt(auVar206,0,4);
            fVar194 = (float)CONCAT13((byte)((uint)auVar206._0_4_ >> 0x18) & ~auVar79[3],
                                      CONCAT12((byte)((uint)auVar206._0_4_ >> 0x10) & ~auVar79[2],
                                               CONCAT11((byte)((uint)auVar206._0_4_ >> 8) &
                                                        ~auVar79[1],
                                                        SUB41(auVar206._0_4_,0) & ~auVar79[0])));
            auVar195._0_8_ =
                 CONCAT17((byte)((uint)auVar206._4_4_ >> 0x18) & ~auVar79[7],
                          CONCAT16((byte)((uint)auVar206._4_4_ >> 0x10) & ~auVar79[6],
                                   CONCAT15((byte)((uint)auVar206._4_4_ >> 8) & ~auVar79[5],
                                            CONCAT14(SUB41(auVar206._4_4_,0) & ~auVar79[4],fVar194))
                                  ));
            auVar195[8] = SUB41(auVar206._8_4_,0) & ~auVar79[8];
            auVar195[9] = (byte)((uint)auVar206._8_4_ >> 8) & ~auVar79[9];
            auVar195[10] = (byte)((uint)auVar206._8_4_ >> 0x10) & ~auVar79[10];
            auVar195[11] = (byte)((uint)auVar206._8_4_ >> 0x18) & ~auVar79[11];
            auVar199[12] = SUB41(auVar206._12_4_,0) & ~auVar79[12];
            auVar199._0_12_ = auVar195;
            auVar199[13] = (byte)((uint)auVar206._12_4_ >> 8) & ~auVar79[13];
            auVar199[14] = (byte)((uint)auVar206._12_4_ >> 0x10) & ~auVar79[14];
            auVar199[15] = (byte)((uint)auVar206._12_4_ >> 0x18) & ~auVar79[15];
            fVar140 = fVar140 + (fVar65 - fVar140) * (fVar86 / (auVar130._0_4_ + fVar157)) * fVar88;
            fVar141 = fVar141 + (fVar72 - fVar141) *
                                (fVar86 / (auVar130._0_4_ + (float)((ulong)auVar158._0_8_ >> 0x20)))
                                * fVar93;
            fVar142 = fVar142 + (fVar74 - fVar142) *
                                (fStack_4d8 / ((float)uStack_4b8 + auVar158._8_4_)) * fVar207;
            fVar143 = fVar143 + (fVar76 - fVar143) *
                                (fStack_4d4 / (fVar203 + auVar166._12_4_)) * fVar208;
            fVar65 = auVar204._0_4_ - fVar78;
            fVar72 = auVar204._4_4_ - fVar82;
            fVar74 = auVar204._8_4_ - fVar84;
            fVar76 = auVar204._12_4_ - fVar85;
            auVar79._0_4_ =
                 (fVar110 /
                 (auVar130._4_4_ +
                 (float)CONCAT13((byte)((uint)fVar116 >> 0x18) & ~auVar125[3],
                                 CONCAT12((byte)((uint)fVar116 >> 0x10) & ~auVar125[2],
                                          CONCAT11((byte)((uint)fVar116 >> 8) & ~auVar125[1],
                                                   SUB41(fVar116,0) & ~auVar125[0]))))) * fVar144;
            auVar79._4_4_ =
                 (fVar110 /
                 (auVar130._4_4_ +
                 (float)CONCAT13(bVar150 & ~auVar125[7],
                                 CONCAT12(bVar149 & ~auVar125[6],
                                          CONCAT11(bVar148 & ~auVar125[5],
                                                   SUB41(fVar104,0) & ~auVar125[4]))))) * fVar145;
            auVar79._8_4_ =
                 (fVar110 /
                 (auVar130._4_4_ +
                 (float)CONCAT13(bVar153 & ~auVar125[11],
                                 CONCAT12(bVar152 & ~auVar125[10],
                                          CONCAT11(bVar151 & ~auVar125[9],
                                                   SUB41(fVar126,0) & ~auVar125[8]))))) * fVar146;
            auVar79._12_4_ =
                 (fVar110 /
                 (auVar130._4_4_ +
                 (float)CONCAT13(bVar156 & ~auVar125[15],
                                 CONCAT12(bVar155 & ~auVar125[14],
                                          CONCAT11(bVar154 & ~auVar125[13],
                                                   SUB41(fVar83,0) & ~auVar125[12]))))) * fVar147;
            fVar78 = fVar78 + (fVar45 - fVar78) * (fVar86 / (auVar130._0_4_ + fVar127)) * fVar144;
            fVar82 = fVar82 + (fVar50 - fVar82) *
                              (fVar86 / (auVar130._0_4_ + (float)((ulong)auVar129._0_8_ >> 0x20))) *
                              fVar145;
            fVar84 = fVar84 + (fVar51 - fVar84) *
                              (fStack_4d8 / ((float)uStack_4b8 + auVar129._8_4_)) * fVar146;
            fVar85 = fVar85 + (fVar52 - fVar85) *
                              (fStack_4d4 / (fVar203 + auVar139._12_4_)) * fVar147;
            fVar117 = fVar140 + fVar167 + (fVar105 - fVar167) *
                                          (fVar110 /
                                          (auVar130._4_4_ +
                                          (float)CONCAT13((byte)((uint)fVar117 >> 0x18) &
                                                          ~auVar197[3],
                                                          CONCAT12((byte)((uint)fVar117 >> 0x10) &
                                                                   ~auVar197[2],
                                                                   CONCAT11((byte)((uint)fVar117 >>
                                                                                  8) & ~auVar197[1],
                                                                            SUB41(fVar117,0) &
                                                                            ~auVar197[0]))))) *
                                          fVar88;
            fVar73 = fVar141 + fVar168 + (fVar107 - fVar168) *
                                         (fVar110 /
                                         (auVar130._4_4_ +
                                         (float)CONCAT13(bVar187 & ~auVar197[7],
                                                         CONCAT12(bVar186 & ~auVar197[6],
                                                                  CONCAT11(bVar185 & ~auVar197[5],
                                                                           SUB41(fVar73,0) &
                                                                           ~auVar197[4]))))) *
                                         fVar93;
            fVar75 = fVar142 + fVar169 + (fVar108 - fVar169) *
                                         (fVar110 /
                                         (auVar130._4_4_ +
                                         (float)CONCAT13(bVar190 & ~auVar197[11],
                                                         CONCAT12(bVar189 & ~auVar197[10],
                                                                  CONCAT11(bVar188 & ~auVar197[9],
                                                                           SUB41(fVar75,0) &
                                                                           ~auVar197[8]))))) *
                                         fVar207;
            fVar77 = fVar143 + fVar170 + (fVar109 - fVar170) *
                                         (fVar110 /
                                         (auVar130._4_4_ +
                                         (float)CONCAT13(bVar193 & ~auVar197[15],
                                                         CONCAT12(bVar192 & ~auVar197[14],
                                                                  CONCAT11(bVar191 & ~auVar197[13],
                                                                           SUB41(fVar77,0) &
                                                                           ~auVar197[12]))))) *
                                         fVar208;
            fVar116 = fVar140 + fVar180 + (fVar97 - fVar180) *
                                          (fVar110 /
                                          (auVar130._4_4_ +
                                          (float)CONCAT13((byte)((uint)fVar89 >> 0x18) &
                                                          ~auVar198[3],
                                                          CONCAT12((byte)((uint)fVar89 >> 0x10) &
                                                                   ~auVar198[2],
                                                                   CONCAT11((byte)((uint)fVar89 >> 8
                                                                                  ) & ~auVar198[1],
                                                                            SUB41(fVar89,0) &
                                                                            ~auVar198[0]))))) *
                                          fVar88;
            fVar104 = fVar141 + fVar182 + (fVar100 - fVar182) *
                                          (fVar110 /
                                          (auVar130._4_4_ +
                                          (float)CONCAT13(bVar173 & ~auVar198[7],
                                                          CONCAT12(bVar172 & ~auVar198[6],
                                                                   CONCAT11(bVar171 & ~auVar198[5],
                                                                            SUB41(fVar98,0) &
                                                                            ~auVar198[4]))))) *
                                          fVar93;
            fVar126 = fVar142 + fVar183 + (fVar101 - fVar183) *
                                          (fVar110 /
                                          (auVar130._4_4_ +
                                          (float)CONCAT13(bVar176 & ~auVar198[11],
                                                          CONCAT12(bVar175 & ~auVar198[10],
                                                                   CONCAT11(bVar174 & ~auVar198[9],
                                                                            SUB41(fVar99,0) &
                                                                            ~auVar198[8]))))) *
                                          fVar207;
            fVar83 = fVar143 + fVar184 + (fVar102 - fVar184) *
                                         (fVar110 /
                                         (auVar130._4_4_ +
                                         (float)CONCAT13(bVar179 & ~auVar198[15],
                                                         CONCAT12(bVar178 & ~auVar198[14],
                                                                  CONCAT11(bVar177 & ~auVar198[13],
                                                                           SUB41(fVar106,0) &
                                                                           ~auVar198[12]))))) *
                                         fVar208;
            fVar89 = fVar78 + fVar87 + (fVar53 - fVar87) * auVar79._0_4_;
            fVar98 = fVar82 + fVar92 + (fVar57 - fVar92) * auVar79._4_4_;
            fVar99 = fVar84 + fVar94 + (fVar58 - fVar94) * auVar79._8_4_;
            fVar106 = fVar85 + fVar95 + (fVar59 - fVar95) * auVar79._12_4_;
            fVar88 = fVar78 + fVar65 + (fVar60 - fVar65) *
                                       (fVar110 / (auVar130._4_4_ + fVar194)) * fVar144;
            fVar93 = fVar82 + fVar72 + (fVar62 - fVar72) *
                                       (fVar110 /
                                       (auVar130._4_4_ + (float)((ulong)auVar195._0_8_ >> 0x20))) *
                                       fVar145;
            fVar52 = fVar84 + fVar74 + (fVar63 - fVar74) *
                                       (fVar110 / (auVar130._4_4_ + auVar195._8_4_)) * fVar146;
            fVar63 = fVar85 + fVar76 + (fVar64 - fVar76) *
                                       (fVar110 / (auVar130._4_4_ + auVar199._12_4_)) * fVar147;
            auVar68._0_4_ = (int)(fVar117 + 0.5);
            auVar68._4_4_ = (int)(fVar73 + 0.5);
            auVar68._8_4_ = (int)(fVar75 + 0.5);
            auVar68._12_4_ = (int)(fVar77 + 0.5);
            auVar54._0_4_ = (int)(fVar89 + 0.5);
            auVar54._4_4_ = (int)(fVar98 + 0.5);
            auVar54._8_4_ = (int)(fVar99 + 0.5);
            auVar54._12_4_ = (int)(fVar106 + 0.5);
            auVar47._0_4_ = (int)(fVar116 + 0.5);
            auVar47._4_4_ = (int)(fVar104 + 0.5);
            auVar47._8_4_ = (int)(fVar126 + 0.5);
            auVar47._12_4_ = (int)(fVar83 + 0.5);
            auVar204._8_4_ = 0xff;
            auVar204._0_8_ = 0xff000000ff;
            auVar204._12_4_ = 0xff;
            auVar125 = NEON_umin(auVar68,auVar204,4);
            auVar198._8_4_ = 0xff;
            auVar198._0_8_ = 0xff000000ff;
            auVar198._12_4_ = 0xff;
            auVar197 = NEON_umin(auVar54,auVar198,4);
            auVar202._8_4_ = 0xff;
            auVar202._0_8_ = 0xff000000ff;
            auVar202._12_4_ = 0xff;
            auVar204 = NEON_umin(auVar47,auVar202,4);
            auVar61._0_4_ = (int)((fVar140 + fVar117 * -0.2126 + fVar116 * -0.0722) / 0.7152 + 0.5);
            auVar61._4_4_ = (int)((fVar141 + fVar73 * -0.2126 + fVar104 * -0.0722) / 0.7152 + 0.5);
            auVar61._8_4_ = (int)((fVar142 + fVar75 * -0.2126 + fVar126 * -0.0722) / 0.7152 + 0.5);
            auVar61._12_4_ = (int)((fVar143 + fVar77 * -0.2126 + fVar83 * -0.0722) / 0.7152 + 0.5);
            auVar80._8_4_ = 0xff;
            auVar80._0_8_ = 0xff000000ff;
            auVar80._12_4_ = 0xff;
            auVar198 = NEON_umin(auVar61,auVar80,4);
            uVar46 = CONCAT26(auVar197._12_2_,
                              CONCAT24(auVar197._8_2_,CONCAT22(auVar197._4_2_,auVar197._0_2_))) &
                     0xff00ff00ff00ff;
            auVar69._0_4_ = (int)((fVar78 + fVar89 * -0.2126 + fVar88 * -0.0722) / 0.7152 + 0.5);
            auVar69._4_4_ = (int)((fVar82 + fVar98 * -0.2126 + fVar93 * -0.0722) / 0.7152 + 0.5);
            auVar69._8_4_ = (int)((fVar84 + fVar99 * -0.2126 + fVar52 * -0.0722) / 0.7152 + 0.5);
            auVar69._12_4_ = (int)((fVar85 + fVar106 * -0.2126 + fVar63 * -0.0722) / 0.7152 + 0.5);
            auVar90._2_2_ = 0;
            auVar90._0_2_ = (ushort)uVar46;
            auVar90._4_2_ = (short)(uVar46 >> 0x10);
            auVar90._6_2_ = 0;
            auVar90._8_2_ = (short)(uVar46 >> 0x20);
            auVar90._10_2_ = 0;
            auVar90._12_2_ = (short)(uVar46 >> 0x30);
            auVar90._14_2_ = 0;
            auVar164._8_4_ = 0xff;
            auVar164._0_8_ = 0xff000000ff;
            auVar164._12_4_ = 0xff;
            auVar202 = NEON_umin(auVar69,auVar164,4);
            auVar70._0_4_ = (int)(fVar88 + 0.5);
            auVar70._4_4_ = (int)(fVar93 + 0.5);
            auVar70._8_4_ = (int)(fVar52 + 0.5);
            auVar70._12_4_ = (int)(fVar63 + 0.5);
            auVar197._6_2_ = 0;
            auVar197._0_6_ = CONCAT24(auVar125._4_2_,(uint)(auVar125._0_2_ & 0xff)) & 0xffffffffff;
            auVar197._8_2_ = auVar125._8_2_ & 0xff;
            auVar197._10_2_ = 0;
            auVar197._12_2_ = auVar125._12_2_ & 0xff;
            auVar197._14_2_ = 0;
            auVar80 = a64_TBL(ZEXT816(0),auVar90,auVar197,_DAT_001004e0);
            uVar46 = CONCAT26(auVar202._12_2_,
                              CONCAT24(auVar202._8_2_,CONCAT22(auVar202._4_2_,auVar202._0_2_))) &
                     0xff00ff00ff00ff;
            auVar7._8_4_ = 0xff;
            auVar7._0_8_ = 0xff000000ff;
            auVar7._12_4_ = 0xff;
            auVar197 = NEON_umin(auVar70,auVar7,4);
            *puVar31 = auVar80[0];
            puVar31[4] = auVar80[1];
            puVar31[8] = auVar80[2];
            puVar31[0xc] = auVar80[3];
            auVar91._2_2_ = 0;
            auVar91._0_2_ = (ushort)uVar46;
            auVar91._4_2_ = (short)(uVar46 >> 0x10);
            auVar91._6_2_ = 0;
            auVar91._8_2_ = (short)(uVar46 >> 0x20);
            auVar91._10_2_ = 0;
            auVar91._12_2_ = (short)(uVar46 >> 0x30);
            auVar91._14_2_ = 0;
            puVar31[0x10] = auVar80[4];
            puVar31[0x14] = auVar80[5];
            auVar125._6_2_ = 0;
            auVar125._0_6_ = CONCAT24(auVar198._4_2_,(uint)(auVar198._0_2_ & 0xff)) & 0xffffffffff;
            auVar125._8_2_ = auVar198._8_2_ & 0xff;
            auVar125._10_2_ = 0;
            auVar125._12_2_ = auVar198._12_2_ & 0xff;
            auVar125._14_2_ = 0;
            auVar125 = a64_TBL(ZEXT816(0),auVar91,auVar125,auVar48);
            puVar31[0x18] = auVar80[6];
            uVar46 = CONCAT26(auVar197._12_2_,
                              CONCAT24(auVar197._8_2_,CONCAT22(auVar197._4_2_,auVar197._0_2_))) &
                     0xff00ff00ff00ff;
            puVar31[0x1c] = auVar80[7];
            puVar31[1] = auVar125[0];
            auVar81._6_2_ = 0;
            auVar81._0_6_ = CONCAT24(auVar204._4_2_,(uint)(auVar204._0_2_ & 0xff)) & 0xffffffffff;
            auVar81._8_2_ = auVar204._8_2_ & 0xff;
            auVar81._10_2_ = 0;
            auVar81._12_2_ = auVar204._12_2_ & 0xff;
            auVar81._14_2_ = 0;
            puVar31[5] = auVar125[1];
            auVar71._2_2_ = 0;
            auVar71._0_2_ = (ushort)uVar46;
            auVar71._4_2_ = (short)(uVar46 >> 0x10);
            auVar71._6_2_ = 0;
            auVar71._8_2_ = (short)(uVar46 >> 0x20);
            auVar71._10_2_ = 0;
            auVar71._12_2_ = (short)(uVar46 >> 0x30);
            auVar71._14_2_ = 0;
            puVar31[9] = auVar125[2];
            puVar31[0xd] = auVar125[3];
            puVar31[0x11] = auVar125[4];
            auVar197 = a64_TBL(ZEXT816(0),auVar71,auVar81,auVar48);
            puVar31[0x15] = auVar125[5];
            puVar31[0x19] = auVar125[6];
            puVar31[0x1d] = auVar125[7];
            puVar31[2] = auVar197[0];
            puVar31[6] = auVar197[1];
            puVar31[10] = auVar197[2];
            puVar31[0xe] = auVar197[3];
            puVar31[0x12] = auVar197[4];
            puVar31[0x16] = auVar197[5];
            puVar31[0x1a] = auVar197[6];
            puVar31[0x1e] = auVar197[7];
          } while (lVar29 != 0);
          auVar118 = ZEXT816(0x3f0000003f000000);
          lVar29 = uVar42 - uVar41;
        }
        pfVar34 = (float *)((long)__s + lVar29 * 0x18 + 0xc);
        uVar37 = lVar29 << 2;
        lVar29 = uVar42 - lVar29;
        do {
          pfVar35 = pfVar34 + -3;
          pfVar2 = pfVar34 + 1;
          pfVar39 = pfVar34 + -2;
          fVar98 = *pfVar34;
          pbVar4 = data + (uVar37 & 0xfffffffc) + uVar28 * uVar43;
          pfVar3 = pfVar34 + 2;
          uVar37 = uVar37 + 4;
          fVar116 = pfVar34[-1] / 49.0;
          pfVar34 = pfVar34 + 6;
          fVar126 = *pfVar35 / 49.0;
          fVar83 = *pfVar2 / 49.0;
          fVar104 = (float)NEON_ucvtf((uint)pbVar4[1]);
          fVar99 = (float)NEON_ucvtf((uint)*pbVar4);
          fVar106 = (float)NEON_ucvtf((uint)pbVar4[2]);
          uVar96 = NEON_fmadd(fVar99,0x3e59b3d0,fVar104 * 0.7152);
          fVar89 = (float)NEON_fmadd(fVar106,0x3d93dd98,uVar96);
          fVar104 = (float)NEON_fmsub(fVar116,fVar116,fVar98 / 49.0);
          vu = 0.0;
          if (0.0 <= fVar104) {
            vu = fVar104;
          }
          dVar67 = (double)CONCAT44(*pfVar3 / 49.0,*pfVar39 / 49.0) -
                   (double)CONCAT44(fVar83 * fVar83,fVar126 * fVar126);
          uVar66 = NEON_fcmlt(dVar67,0,4);
          fVar104 = (float)CONCAT13((byte)((ulong)dVar67 >> 0x18) & ~(byte)((ulong)uVar66 >> 0x18),
                                    CONCAT12((byte)((ulong)dVar67 >> 0x10) &
                                             ~(byte)((ulong)uVar66 >> 0x10),
                                             CONCAT11((byte)((ulong)dVar67 >> 8) &
                                                      ~(byte)((ulong)uVar66 >> 8),
                                                      SUB81(dVar67,0) & ~(byte)uVar66)));
          fVar117 = 1.0 / (((fVar89 - fVar126) * (fVar89 - fVar126)) / fVar103 + 1.0);
          fVar116 = (float)NEON_fmadd((fVar110 / (auVar130._4_4_ + vu)) * fVar117,
                                      fVar116 - (fVar99 - fVar89),fVar99 - fVar89);
          fVar98 = fVar89 + (fVar126 - fVar89) * (fVar86 / (auVar130._0_4_ + fVar104)) * fVar117;
          fVar126 = fVar98 + (fVar106 - fVar89) +
                             (fVar83 - (fVar106 - fVar89)) *
                             (fVar110 /
                             (auVar130._4_4_ +
                             (float)(CONCAT17((byte)((ulong)dVar67 >> 0x38) &
                                              ~(byte)((ulong)uVar66 >> 0x38),
                                              CONCAT16((byte)((ulong)dVar67 >> 0x30) &
                                                       ~(byte)((ulong)uVar66 >> 0x30),
                                                       CONCAT15((byte)((ulong)dVar67 >> 0x28) &
                                                                ~(byte)((ulong)uVar66 >> 0x28),
                                                                CONCAT14((byte)((ulong)dVar67 >>
                                                                               0x20) &
                                                                         ~(byte)((ulong)uVar66 >>
                                                                                0x20),fVar104)))) >>
                                    0x20))) * fVar117;
          uVar96 = NEON_fmadd(fVar98 + fVar116,0xbe59b3d0,fVar98);
          fVar104 = (float)NEON_fmadd(fVar126,0xbd93dd98,uVar96);
          iVar40 = (int)(fVar126 + 0.5);
          if (0xfe < iVar40) {
            iVar40 = 0xff;
          }
          lVar29 = lVar29 + -1;
          uVar66 = NEON_smin(CONCAT44((int)(fVar104 / 0.7152 + auVar118._4_4_),
                                      (int)(fVar98 + fVar116 + auVar118._0_4_)),0xff000000ff,4);
          pbVar4[2] = (byte)iVar40 & ((byte)(iVar40 >> 0x1f) ^ 0xff);
          uVar66 = NEON_smax(uVar66,0,4);
          *pbVar4 = (byte)uVar66;
          pbVar4[1] = (byte)((ulong)uVar66 >> 0x20);
        } while (lVar29 != 0);
      }
      uVar37 = uVar28 + 1;
      if (uVar37 < (uint)h) {
        iVar40 = (int)uVar28;
        iVar30 = (int)((uVar28 & 0xffffffff) * 0x24924925 >> 0x20);
        pfVar34 = (float *)((long)out +
                           uVar27 * (iVar40 + (iVar30 + ((uint)(iVar40 - iVar30) >> 1) >> 2) * -7) *
                           4);
        if (w == 0) {
          horizontal(data,0,h,stride,iVar40 + 4,pfVar34);
        }
        else {
          lVar29 = uVar28 + (uVar28 / 7 + (uVar28 - uVar28 / 7 >> 1) >> 2) * -7;
          lVar32 = uVar42 * 0x18 * lVar29;
          pauVar44 = (undefined (*) [16])((long)out + uVar42 * 0x18 * lVar29 + 0x10);
          uVar28 = uVar24;
          pauVar33 = (undefined (*) [16])(__s + 1);
          pauVar38 = pauVar44;
          if (w == 1) {
            uVar28 = 0;
LAB_001053b0:
            lVar29 = uVar42 * -6 + uVar28;
            pfVar35 = (float *)((long)__s + uVar28 * 4);
            pfVar39 = (float *)((long)out + lVar32 + uVar28 * 4);
            do {
              bVar21 = lVar29 != -1;
              lVar29 = lVar29 + 1;
              *pfVar35 = *pfVar35 - *pfVar39;
              pfVar35 = pfVar35 + 1;
              pfVar39 = pfVar39 + 1;
            } while (bVar21);
          }
          else {
            do {
              auVar79 = pauVar33[-1];
              auVar197 = *pauVar33;
              uVar28 = uVar28 - 8;
              auVar125 = pauVar38[-1];
              auVar204 = *pauVar38;
              auVar48._0_8_ =
                   CONCAT44(auVar79._4_4_ - auVar125._4_4_,auVar79._0_4_ - auVar125._0_4_);
              auVar48._8_4_ = auVar79._8_4_ - auVar125._8_4_;
              auVar48._12_4_ = auVar79._12_4_ - auVar125._12_4_;
              auVar55._0_8_ =
                   CONCAT44(auVar197._4_4_ - auVar204._4_4_,auVar197._0_4_ - auVar204._0_4_);
              auVar55._8_4_ = auVar197._8_4_ - auVar204._8_4_;
              auVar55._12_4_ = auVar197._12_4_ - auVar204._12_4_;
              *(long *)((long)pauVar33[-1] + 8) = auVar48._8_8_;
              *(undefined8 *)pauVar33[-1] = auVar48._0_8_;
              *(long *)((long)*pauVar33 + 8) = auVar55._8_8_;
              *(undefined8 *)*pauVar33 = auVar55._0_8_;
              pauVar33 = pauVar33 + 2;
              pauVar38 = pauVar38 + 2;
            } while (uVar28 != 0);
            uVar28 = uVar24;
            if (uVar27 != uVar24) goto LAB_001053b0;
          }
          horizontal(data,w,h,stride,iVar40 + 4,pfVar34);
          if (w != 0) {
            uVar28 = uVar24;
            pauVar33 = (undefined (*) [16])(__s + 1);
            if (w == 1) {
              uVar28 = 0;
            }
            else {
              do {
                auVar79 = pauVar33[-1];
                auVar197 = *pauVar33;
                uVar28 = uVar28 - 8;
                auVar125 = pauVar44[-1];
                auVar204 = *pauVar44;
                pauVar44 = pauVar44 + 2;
                auVar49._0_8_ =
                     CONCAT44(auVar125._4_4_ + auVar79._4_4_,auVar125._0_4_ + auVar79._0_4_);
                auVar49._8_4_ = auVar125._8_4_ + auVar79._8_4_;
                auVar49._12_4_ = auVar125._12_4_ + auVar79._12_4_;
                auVar56._0_8_ =
                     CONCAT44(auVar204._4_4_ + auVar197._4_4_,auVar204._0_4_ + auVar197._0_4_);
                auVar56._8_4_ = auVar204._8_4_ + auVar197._8_4_;
                auVar56._12_4_ = auVar204._12_4_ + auVar197._12_4_;
                *(long *)((long)pauVar33[-1] + 8) = auVar49._8_8_;
                *(undefined8 *)pauVar33[-1] = auVar49._0_8_;
                *(long *)((long)*pauVar33 + 8) = auVar56._8_8_;
                *(undefined8 *)*pauVar33 = auVar56._0_8_;
                pauVar33 = pauVar33 + 2;
              } while (uVar28 != 0);
              uVar28 = uVar24;
              if (uVar27 == uVar24) goto LAB_00104d04;
            }
            lVar29 = uVar42 * -6 + uVar28;
            pfVar34 = (float *)((long)__s + uVar28 * 4);
            pfVar35 = (float *)((long)out + lVar32 + uVar28 * 4);
            do {
              bVar21 = lVar29 != -1;
              lVar29 = lVar29 + 1;
              *pfVar34 = *pfVar35 + *pfVar34;
              pfVar34 = pfVar34 + 1;
              pfVar35 = pfVar35 + 1;
            } while (bVar21);
          }
        }
      }
LAB_00104d04:
      uVar28 = uVar37;
    } while (uVar37 != (uint)h);
  }
  iVar40 = 1;
  pVar22 = __s;
  __s = out;
LAB_001054ac:
  free(pVar22);
  free(__s);
  return iVar40;
}



/* 0010591c horizontal */

/* WARNING: Unknown calling convention */

void horizontal(u8 *data,int w,int h,int stride,int y,float *out)

{
  int iVar1;
  byte *pbVar2;
  byte *pbVar3;
  byte *pbVar4;
  int iVar5;
  uint uVar6;
  int iVar7;
  bool bVar8;
  uint uVar9;
  byte *pbVar10;
  u8 *row;
  ulong uVar11;
  float *pfVar12;
  u8 *p;
  u8 *a;
  u8 *b;
  undefined8 uVar13;
  float fVar14;
  undefined4 uVar15;
  float yy;
  undefined8 uVar16;
  float fVar17;
  float fVar18;
  float v;
  float fVar19;
  float fVar20;
  float u;
  float ay;
  float fVar21;
  float fVar22;
  float by;
  float fVar23;
  float au;
  float fVar24;
  undefined4 uVar25;
  float fVar26;
  float bu;
  float fVar27;
  float av;
  float fVar28;
  float fVar29;
  float bv;
  float fVar30;
  undefined4 uVar31;
  float fVar32;
  float fVar33;
  undefined4 uVar34;
  undefined4 uVar35;
  undefined4 uVar36;
  
  uVar9 = y;
  if ((int)(h - 1U) <= y) {
    uVar9 = h - 1U;
  }
  uVar6 = 0;
  if (-1 < y) {
    uVar6 = uVar9;
  }
  iVar7 = w + -1;
  if (0 < w) {
    pbVar10 = data + (ulong)uVar6 * (ulong)(uint)stride;
    uVar13 = NEON_smin(CONCAT44(iVar7,iVar7),DAT_001004c8,4);
    uVar16 = NEON_smin(CONCAT44(iVar7,iVar7),DAT_001004c0,4);
    fVar14 = (float)NEON_ucvtf((uint)pbVar10[1]);
    fVar20 = (float)NEON_ucvtf((uint)*pbVar10);
    uVar9 = 0;
    fVar17 = (float)NEON_ucvtf((uint)pbVar10[2]);
    uVar15 = NEON_fmadd(fVar20,0x3e59b3d0,fVar14 * 0.7152);
    pbVar2 = pbVar10 + (uint)((int)uVar13 << 2);
    pbVar3 = pbVar10 + (uint)((int)((ulong)uVar13 >> 0x20) << 2);
    pbVar4 = pbVar10 + (uint)((int)((ulong)uVar16 >> 0x20) << 2);
    fVar14 = (float)NEON_fmadd(fVar17,0x3d93dd98,uVar15);
    fVar24 = (float)NEON_ucvtf((uint)pbVar2[1]);
    fVar21 = (float)NEON_ucvtf((uint)pbVar3[1]);
    fVar23 = (float)NEON_ucvtf((uint)*pbVar2);
    fVar19 = (float)NEON_ucvtf((uint)pbVar2[2]);
    fVar28 = (float)NEON_ucvtf((uint)pbVar4[1]);
    fVar30 = (float)NEON_ucvtf((uint)pbVar3[2]);
    fVar17 = fVar17 - fVar14;
    fVar20 = fVar20 - fVar14;
    pbVar2 = pbVar10 + (uint)((int)uVar16 << 2);
    fVar18 = (float)NEON_ucvtf((uint)*pbVar3);
    uVar34 = NEON_fmadd(fVar14,fVar14,0);
    fVar27 = (float)NEON_ucvtf((uint)*pbVar4);
    uVar31 = NEON_fmadd(fVar17,fVar17,0);
    uVar36 = NEON_fmadd(fVar20,fVar20,0);
    fVar33 = (float)NEON_ucvtf((uint)pbVar2[1]);
    uVar25 = NEON_fmadd(fVar23,0x3e59b3d0,fVar24 * 0.7152);
    uVar15 = NEON_fmadd(fVar18,0x3e59b3d0,fVar21 * 0.7152);
    uVar35 = NEON_fmadd(fVar14,fVar14,uVar34);
    fVar32 = (float)NEON_ucvtf((uint)*pbVar2);
    fVar24 = (float)NEON_ucvtf((uint)pbVar4[2]);
    uVar34 = NEON_fmadd(fVar27,0x3e59b3d0,fVar28 * 0.7152);
    uVar31 = NEON_fmadd(fVar17,fVar17,uVar31);
    uVar36 = NEON_fmadd(fVar20,fVar20,uVar36);
    fVar26 = (float)NEON_fmadd(fVar19,0x3d93dd98,uVar25);
    fVar22 = (float)NEON_fmadd(fVar30,0x3d93dd98,uVar15);
    uVar35 = NEON_fmadd(fVar14,fVar14,uVar35);
    pfVar12 = out + 3;
    fVar29 = (float)NEON_fmadd(fVar24,0x3d93dd98,uVar34);
    uVar15 = NEON_fmadd(fVar17,fVar17,uVar31);
    uVar34 = NEON_fmadd(fVar20,fVar20,uVar36);
    fVar19 = fVar19 - fVar26;
    fVar30 = fVar30 - fVar22;
    fVar18 = fVar18 - fVar22;
    fVar23 = fVar23 - fVar26;
    fVar28 = (float)NEON_ucvtf((uint)pbVar2[2]);
    uVar25 = NEON_fmadd(fVar32,0x3e59b3d0,fVar33 * 0.7152);
    uVar31 = NEON_fmadd(fVar22,fVar22,uVar35);
    fVar24 = fVar24 - fVar29;
    uVar11 = (ulong)(uint)w;
    fVar27 = fVar27 - fVar29;
    uVar15 = NEON_fmadd(fVar30,fVar30,uVar15);
    uVar34 = NEON_fmadd(fVar18,fVar18,uVar34);
    fVar33 = (float)NEON_fmadd(fVar28,0x3d93dd98,uVar25);
    uVar15 = NEON_fmadd(fVar19,fVar19,uVar15);
    uVar25 = NEON_fmadd(fVar23,fVar23,uVar34);
    uVar34 = NEON_fmadd(fVar26,fVar26,uVar31);
    fVar28 = fVar28 - fVar33;
    fVar32 = fVar32 - fVar33;
    uVar15 = NEON_fmadd(fVar24,fVar24,uVar15);
    uVar25 = NEON_fmadd(fVar27,fVar27,uVar25);
    uVar34 = NEON_fmadd(fVar29,fVar29,uVar34);
    fVar21 = (float)NEON_fmadd(fVar28,fVar28,uVar15);
    fVar28 = fVar28 + fVar24 + fVar19 + fVar30 + fVar17 + fVar17 + fVar17;
    fVar24 = (float)NEON_fmadd(fVar32,fVar32,uVar25);
    fVar32 = fVar32 + fVar27 + fVar23 + fVar18 + fVar20 + fVar20 + fVar20;
    fVar17 = (float)NEON_fmadd(fVar33,fVar33,uVar34);
    fVar33 = fVar14 + 0.0 + fVar14 + fVar14 + fVar22 + fVar26 + fVar29 + fVar33;
    do {
      iVar1 = uVar9 + 4;
      pfVar12[-3] = fVar33;
      pfVar12[-2] = fVar17;
      pfVar12[-1] = fVar32;
      *pfVar12 = fVar24;
      iVar5 = uVar9 - 3;
      if (iVar7 <= (int)(uVar9 - 3)) {
        iVar5 = iVar7;
      }
      bVar8 = 2 < uVar9;
      pfVar12[1] = fVar28;
      pfVar12[2] = fVar21;
      uVar9 = uVar9 + 1;
      pfVar12 = pfVar12 + 6;
      uVar6 = 0;
      if (bVar8) {
        uVar6 = iVar5 << 2;
      }
      pbVar2 = pbVar10 + uVar6;
      if (iVar7 <= iVar1) {
        iVar1 = iVar7;
      }
      uVar11 = uVar11 - 1;
      fVar14 = (float)NEON_ucvtf((uint)pbVar2[1]);
      pbVar3 = pbVar10 + (uint)(iVar1 << 2);
      fVar20 = (float)NEON_ucvtf((uint)*pbVar2);
      fVar27 = (float)NEON_ucvtf((uint)pbVar2[2]);
      fVar18 = (float)NEON_ucvtf((uint)pbVar3[1]);
      fVar22 = (float)NEON_ucvtf((uint)*pbVar3);
      fVar23 = (float)NEON_ucvtf((uint)pbVar3[2]);
      uVar15 = NEON_fmadd(fVar20,0x3e59b3d0,fVar14 * 0.7152);
      uVar25 = NEON_fmadd(fVar22,0x3e59b3d0,fVar18 * 0.7152);
      fVar14 = (float)NEON_fmadd(fVar27,0x3d93dd98,uVar15);
      fVar18 = (float)NEON_fmadd(fVar23,0x3d93dd98,uVar25);
      fVar20 = fVar20 - fVar14;
      fVar27 = fVar27 - fVar14;
      fVar22 = fVar22 - fVar18;
      fVar23 = fVar23 - fVar18;
      fVar19 = (float)NEON_fmadd(fVar18,fVar18,-(fVar14 * fVar14));
      fVar33 = fVar33 + (fVar18 - fVar14);
      fVar14 = (float)NEON_fmadd(fVar22,fVar22,-(fVar20 * fVar20));
      fVar18 = (float)NEON_fmadd(fVar23,fVar23,-(fVar27 * fVar27));
      fVar17 = fVar17 + fVar19;
      fVar32 = fVar32 + (fVar22 - fVar20);
      fVar28 = (fVar23 - fVar27) + fVar28;
      fVar24 = fVar14 + fVar24;
      fVar21 = fVar18 + fVar21;
    } while (uVar11 != 0);
  }
  return;
}



/* 00105c14 Java_com_codex_lmport_DenoiseFlow_filter */

/* WARNING: Unknown calling convention */

uchar Java_com_codex_lmport_DenoiseFlow_filter(void *env,void *cls,void *bitmap,uchar finishing)

{
  uchar uVar1;
  int iVar2;
  int ok;
  void *pixels;
  BitmapInfo i;
  u8 *local_40;
  int local_34;
  int iStack_30;
  int local_2c;
  int local_28;
  int local_24;
  
  local_40 = (u8 *)0x0;
  iVar2 = AndroidBitmap_getInfo(env,bitmap,&local_34);
  uVar1 = '\0';
  if (((iVar2 == 0) && (local_28 == 1)) && (-1 < local_24)) {
    iVar2 = AndroidBitmap_lockPixels(env,bitmap,&local_40);
    if (iVar2 == 0) {
      iVar2 = leica_filter(local_40,local_34,iStack_30,local_2c,(uint)(finishing != '\0'));
      uVar1 = (uchar)iVar2;
      AndroidBitmap_unlockPixels(env,bitmap);
    }
    else {
      uVar1 = '\0';
    }
  }
  return uVar1;
}



/* 00105cc0 FUN_00105cc0 */

void FUN_00105cc0(void)

{
  (*(code *)PTR_00109e60)();
  return;
}



/* 00105ce0 leica_filter */

/* WARNING: Unknown calling convention */

int leica_filter(u8 *data,int w,int h,int stride,int finishing)

{
  int iVar1;
  
  iVar1 = (*(code *)PTR_leica_filter_00109e68)((int)data,w,h,stride,finishing);
  return iVar1;
}



/* 00105cf0 malloc */

/* WARNING: Unknown calling convention -- yet parameter storage is locked */

void * malloc(size_t __size)

{
  void *pvVar1;
  
  pvVar1 = (void *)(*(code *)PTR_malloc_00109e70)();
  return pvVar1;
}



/* 00105d00 memset */

/* WARNING: Unknown calling convention -- yet parameter storage is locked */

void * memset(void *__s,int __c,size_t __n)

{
  void *pvVar1;
  
  pvVar1 = (void *)(*(code *)PTR_memset_00109e78)(__s,__c);
  return pvVar1;
}



/* 00105d10 free */

/* WARNING: Unknown calling convention -- yet parameter storage is locked */

void free(void *__ptr)

{
  (*(code *)PTR_free_00109e80)();
  return;
}



/* 00105d20 AndroidBitmap_getInfo */

void AndroidBitmap_getInfo(void)

{
  (*(code *)PTR_AndroidBitmap_getInfo_00109e88)();
  return;
}



/* 00105d30 AndroidBitmap_lockPixels */

void AndroidBitmap_lockPixels(void)

{
  (*(code *)PTR_AndroidBitmap_lockPixels_00109e90)();
  return;
}



/* 00105d40 AndroidBitmap_unlockPixels */

void AndroidBitmap_unlockPixels(void)

{
  (*(code *)PTR_AndroidBitmap_unlockPixels_00109e98)();
  return;
}



/* 0010a000 malloc */

/* WARNING: Control flow encountered bad instruction data */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

void * malloc(size_t __size)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}



/* 0010a008 memset */

/* WARNING: Control flow encountered bad instruction data */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

void * memset(void *__s,int __c,size_t __n)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}



/* 0010a010 free */

/* WARNING: Control flow encountered bad instruction data */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

void free(void *__ptr)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}



/* 0010a018 AndroidBitmap_getInfo */

/* WARNING: Control flow encountered bad instruction data */

void AndroidBitmap_getInfo(void)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}



/* 0010a020 AndroidBitmap_lockPixels */

/* WARNING: Control flow encountered bad instruction data */

void AndroidBitmap_lockPixels(void)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}



/* 0010a028 AndroidBitmap_unlockPixels */

/* WARNING: Control flow encountered bad instruction data */

void AndroidBitmap_unlockPixels(void)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}


