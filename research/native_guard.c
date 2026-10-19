/* Image base: 00100000 */

/* 0057ea3c snapshot_impl */

undefined8 *
snapshot_impl(long param_1,uint param_2,uint param_3,int param_4,undefined4 param_5,int param_6)

{
  int iVar1;
  int iVar2;
  int iVar3;
  undefined8 *__ptr;
  void *__ptr_00;
  void *__ptr_01;
  void *__ptr_02;
  ulong uVar4;
  ulong uVar5;
  int iVar6;
  int *piVar7;
  ulong uVar8;
  long lVar9;
  float fVar10;
  int iVar11;
  undefined8 uVar12;
  int iVar13;
  float fVar14;
  float fVar15;
  float fVar16;
  undefined8 uVar17;
  undefined8 uVar18;
  undefined8 *local_24a0;
  long lStack_2498;
  uint local_2490;
  uint uStack_248c;
  int local_2488;
  undefined4 uStack_2484;
  float *local_2480;
  int *piStack_2478;
  int local_246c [2049];
  float local_468 [258];
  
  if (0x8000 < (int)param_3) {
    return (undefined8 *)0x0;
  }
  if (0x8000 < (int)param_2) {
    return (undefined8 *)0x0;
  }
  if (param_1 == 0) {
    return (undefined8 *)0x0;
  }
  if ((int)param_2 < 1) {
    return (undefined8 *)0x0;
  }
  if ((int)param_3 < 1) {
    return (undefined8 *)0x0;
  }
  if (param_4 < (int)(param_2 * 4)) {
    return (undefined8 *)0x0;
  }
  if (80000000 < (ulong)param_3 * (ulong)param_2) {
    return (undefined8 *)0x0;
  }
  __ptr = (undefined8 *)calloc(1,0x28);
  if (__ptr == (undefined8 *)0x0) {
    return (undefined8 *)0x0;
  }
  fVar10 = (float)param_2;
  fVar14 = (float)(ulong)param_3;
  *(uint *)(__ptr + 1) = param_2;
  *(uint *)((long)__ptr + 0xc) = param_3;
  fVar16 = fVar10;
  if (fVar10 <= fVar14) {
    fVar16 = fVar14;
  }
  fVar15 = 1.0;
  if (2048.0 / fVar16 <= 1.0) {
    fVar15 = 2048.0 / fVar16;
  }
  uVar17 = NEON_fmov(0x3f800000,4);
  uVar12 = NEON_scvtf(CONCAT44((int)(fVar14 * fVar15),(int)(fVar10 * fVar15)),4);
  uVar18 = NEON_fcmgt(uVar17,uVar12,4);
  uVar12 = NEON_bit(uVar12,uVar17,uVar18,1);
  iVar11 = (int)(float)uVar12;
  iVar13 = (int)(float)((ulong)uVar12 >> 0x20);
  *__ptr = CONCAT44(iVar13,iVar11);
  lVar9 = (long)iVar11 * (long)iVar13;
  __ptr_00 = malloc(lVar9 * 4);
  __ptr[2] = __ptr_00;
  if (param_6 == 0) {
    __ptr_01 = (void *)0x0;
    __ptr[4] = 0;
    __ptr_02 = malloc(lVar9 * 3);
    __ptr[3] = __ptr_02;
  }
  else {
    __ptr_01 = malloc(lVar9 * 4);
    __ptr[4] = __ptr_01;
    __ptr_02 = malloc(lVar9 * 3);
    __ptr[3] = __ptr_02;
  }
  if (((__ptr_00 == (void *)0x0) || (__ptr_01 == (void *)0x0 && param_6 != 0)) ||
     (__ptr_02 == (void *)0x0)) {
    free(__ptr_00);
    free(__ptr_02);
    free(__ptr_01);
    free(__ptr);
    return (undefined8 *)0x0;
  }
  lVar9 = 0;
  do {
    fVar10 = 1.0;
    fVar16 = (float)(ulong)((uint)lVar9 & 0xff) * 16.06275;
    iVar6 = (int)fVar16;
    if (iVar6 < 0x1000) {
      fVar10 = *(float *)(&RICH_DECODE + (long)iVar6 * 4) +
               (fVar16 - (float)iVar6) *
               (*(float *)(&DAT_0055d804 + (long)iVar6 * 4) -
               *(float *)(&RICH_DECODE + (long)iVar6 * 4));
    }
    local_468[lVar9] = fVar10;
    lVar9 = lVar9 + 1;
  } while (lVar9 != 0x100);
  if (-1 < iVar11) {
    uVar4 = (ulong)(iVar11 + 1);
    if (iVar11 == 0) {
      uVar5 = 0;
    }
    else {
      uVar5 = uVar4 & 0xfffffffe;
      iVar6 = 0;
      piVar7 = local_246c + 1;
      uVar8 = uVar5;
      do {
        iVar1 = param_2 + iVar6;
        iVar2 = 0;
        if (iVar11 != 0) {
          iVar2 = iVar6 / iVar11;
        }
        uVar8 = uVar8 - 2;
        iVar6 = iVar6 + param_2 * 2;
        iVar3 = 0;
        if (iVar11 != 0) {
          iVar3 = iVar1 / iVar11;
        }
        piVar7[-1] = iVar2;
        *piVar7 = iVar3;
        piVar7 = piVar7 + 2;
      } while (uVar8 != 0);
      if (uVar5 == uVar4) goto LAB_0057ecb0;
    }
    iVar6 = param_2 * (int)uVar5;
    lVar9 = uVar4 - uVar5;
    piVar7 = local_246c + uVar5;
    do {
      iVar1 = 0;
      if (iVar11 != 0) {
        iVar1 = iVar6 / iVar11;
      }
      lVar9 = lVar9 + -1;
      iVar6 = iVar6 + param_2;
      *piVar7 = iVar1;
      piVar7 = piVar7 + 1;
    } while (lVar9 != 0);
  }
LAB_0057ecb0:
  piStack_2478 = local_246c;
  local_2480 = local_468;
  local_24a0 = __ptr;
  lStack_2498 = param_1;
  local_2490 = param_2;
  uStack_248c = param_3;
  local_2488 = param_4;
  uStack_2484 = param_5;
  b6_rows(iVar13,iVar11,snapshot_rows,&local_24a0);
  return __ptr;
}



/* 0057ed0c b6_reference_snapshot */

void b6_reference_snapshot(void)

{
  snapshot_impl();
  return;
}



/* 0057ed14 b4_guard */

void b4_guard(void)

{
  guard_impl(0);
  return;
}



/* 0057ed1c guard_impl */

undefined8
guard_impl(float param_1,uint *param_2,long param_3,uint param_4,uint param_5,int param_6,
          int param_7,int param_8,undefined8 *param_9)

{
  undefined (*pauVar1) [16];
  int iVar2;
  uint uVar3;
  uint uVar4;
  int iVar5;
  size_t sVar6;
  long lVar7;
  uint uVar8;
  int iVar9;
  uint uVar10;
  int iVar11;
  bool bVar12;
  ulong uVar13;
  bool bVar14;
  bool bVar15;
  uint *__ptr;
  float *__ptr_00;
  size_t sVar16;
  float *pfVar17;
  float *pfVar18;
  void *__ptr_01;
  long lVar19;
  ulong uVar20;
  ulong uVar21;
  int iVar22;
  ulong uVar23;
  undefined (*pauVar24) [16];
  long lVar25;
  undefined8 uVar26;
  ulong uVar27;
  size_t __nmemb;
  uint uVar28;
  uint uVar29;
  int iVar30;
  byte bVar31;
  ushort uVar32;
  byte bVar36;
  float fVar33;
  byte bVar37;
  byte bVar38;
  ulong uVar34;
  ulong uVar35;
  byte bVar39;
  float fVar40;
  float fVar41;
  byte bVar43;
  byte bVar44;
  byte bVar45;
  ulong uVar42;
  undefined auVar46 [16];
  float fVar47;
  undefined auVar48 [16];
  float fVar49;
  uint *local_4e8;
  float *pfStack_4e0;
  long local_4d8;
  uint local_4d0;
  uint uStack_4cc;
  int local_4c8;
  int iStack_4c4;
  float *local_4c0;
  void *pvStack_4b8;
  float local_4b0 [256];
  uint *local_b0;
  uint *puStack_a8;
  float *local_a0;
  float *local_98;
  int local_90;
  int iStack_8c;
  float *local_88;
  undefined8 local_80;
  
  if (param_9 != (undefined8 *)0x0) {
    param_9[4] = 0;
    param_9[1] = 0;
    *param_9 = 0;
    param_9[3] = 0;
    param_9[2] = 0;
  }
  if (0x8000 < (int)param_5) {
    return 0;
  }
  if (0x8000 < (int)param_4) {
    return 0;
  }
  if (param_3 == 0) {
    return 0;
  }
  if ((int)param_4 < 1) {
    return 0;
  }
  if ((int)param_5 < 1) {
    return 0;
  }
  if (param_6 < (int)(param_4 * 4)) {
    return 0;
  }
  if (80000000 < (ulong)param_5 * (ulong)param_4) {
    return 0;
  }
  __ptr = (uint *)snapshot_impl(param_3,param_4,param_5,param_6,param_7,1);
  if (__ptr == (uint *)0x0) {
    return 0;
  }
  if (param_2 == (uint *)0x0) {
    uVar28 = *__ptr;
    uVar29 = __ptr[1];
  }
  else if ((((param_2[2] != param_4) || (param_2[3] != param_5)) ||
           (uVar28 = *param_2, uVar28 != *__ptr)) || (uVar29 = param_2[1], uVar29 != __ptr[1]))
  goto LAB_0057ef1c;
  __nmemb = (long)(int)uVar29 * (long)(int)uVar28;
  __ptr_00 = (float *)calloc(__nmemb,4);
  if (__ptr_00 == (float *)0x0) {
LAB_0057ef1c:
    free(*(void **)(__ptr + 4));
    free(*(void **)(__ptr + 6));
    free(*(void **)(__ptr + 8));
    free(__ptr);
    return 0;
  }
  local_98 = (float *)0x0;
  local_88 = (float *)0x0;
  local_80 = 0;
  local_b0 = param_2;
  puStack_a8 = __ptr;
  local_a0 = __ptr_00;
  local_90 = param_7;
  iStack_8c = param_8;
  b6_rows(uVar29,uVar28,detect_rows,&local_b0);
  bVar15 = param_7 == 0;
  bVar12 = param_8 != 0;
  if (0.0 < param_1 && (bVar15 && bVar12)) {
    b12_soft_rim(param_1,__ptr,__ptr_00);
  }
  uVar28 = *__ptr;
  uVar29 = __ptr[1];
  iVar22 = uVar28 + 0x3e;
  if ((int)(uVar28 + 0x1f) < 0 == SCARRY4(uVar28,0x1f)) {
    iVar22 = uVar28 + 0x1f;
  }
  iVar11 = uVar29 + 0x3e;
  if ((int)(uVar29 + 0x1f) < 0 == SCARRY4(uVar29,0x1f)) {
    iVar11 = uVar29 + 0x1f;
  }
  iVar22 = iVar22 >> 5;
  sVar16 = (long)(iVar11 >> 5) * (long)iVar22;
  pfVar17 = (float *)calloc(sVar16,1);
  uVar13 = DAT_00100ae0;
  if (((int)uVar29 < 1) || ((int)uVar28 < 1)) {
    pfVar18 = (float *)0x0;
    local_80 = CONCAT44(local_80._4_4_,iVar22);
    local_88 = pfVar17;
  }
  else {
    lVar25 = 0;
    uVar27 = 0;
    bVar14 = false;
    uVar10 = (iVar11 >> 5) - 1;
    iVar11 = iVar22 + -1;
    do {
      uVar4 = (uint)(uVar27 >> 5) & 0x7ffffff;
      uVar8 = uVar10;
      if ((int)(uVar4 + 1) <= (int)uVar10) {
        uVar8 = uVar4 + 1;
      }
      if (0 < (int)uVar28) {
        uVar3 = uVar4 - 1;
        if ((int)uVar10 <= (int)(uVar4 - 1)) {
          uVar3 = uVar10;
        }
        uVar4 = 0;
        if (0x1f < uVar27) {
          uVar4 = uVar3;
        }
        if (pfVar17 == (float *)0x0) {
          uVar8 = uVar28;
          if ((int)uVar28 < 2) {
            uVar8 = 1;
          }
          if (0.0 < __ptr_00[uVar27 * uVar28]) {
            bVar14 = true;
          }
          if (1 < (int)uVar28) {
            if ((int)uVar28 < 9) {
              uVar20 = 1;
            }
            else {
              pauVar24 = (undefined (*) [16])((long)__ptr_00 + lVar25 * (ulong)uVar28 + 0x14);
              uVar34 = 0;
              uVar42 = 0;
              uVar21 = (ulong)uVar8 - 1;
              uVar23 = uVar21 & 0xfffffffffffffff8;
              uVar20 = uVar23 | 1;
              uVar35 = uVar23;
              do {
                pauVar1 = pauVar24 + -1;
                auVar48 = *pauVar24;
                uVar35 = uVar35 - 8;
                pauVar24 = pauVar24 + 2;
                auVar46 = NEON_fcmgt(*pauVar1,0,4);
                auVar48 = NEON_fcmgt(auVar48,0,4);
                bVar31 = (byte)uVar34 | auVar46[0];
                bVar36 = (byte)(uVar34 >> 0x10) | auVar46[4];
                bVar37 = (byte)(uVar34 >> 0x20) | auVar46[8];
                bVar38 = (byte)(uVar34 >> 0x30) | auVar46[12];
                uVar34 = (ulong)CONCAT16(bVar38,(uint6)CONCAT14(bVar37,(uint)CONCAT12(bVar36,(ushort
                                                  )bVar31)));
                bVar39 = (byte)uVar42 | auVar48[0];
                bVar43 = (byte)(uVar42 >> 0x10) | auVar48[4];
                bVar44 = (byte)(uVar42 >> 0x20) | auVar48[8];
                bVar45 = (byte)(uVar42 >> 0x30) | auVar48[12];
                uVar42 = (ulong)CONCAT16(bVar45,(uint6)CONCAT14(bVar44,(uint)CONCAT12(bVar43,(ushort
                                                  )bVar39)));
              } while (uVar35 != 0);
              uVar35 = NEON_cmlt(CONCAT26((ushort)(bVar45 | bVar38) << 0xf,
                                          CONCAT24((ushort)(bVar44 | bVar37) << 0xf,
                                                   CONCAT22((ushort)(bVar43 | bVar36) << 0xf,
                                                            (ushort)(bVar39 | bVar31) << 0xf))),0,2)
              ;
              uVar32 = NEON_addv(uVar35 & uVar13,2);
              if ((uVar32 & 0xf) != 0) {
                bVar14 = true;
              }
              if (uVar21 == uVar23) goto LAB_0057ef54;
            }
            lVar19 = uVar8 - uVar20;
            pfVar18 = (float *)((long)__ptr_00 + lVar25 * (ulong)uVar28 + uVar20 * 4);
            do {
              if (0.0 < *pfVar18) {
                bVar14 = true;
              }
              lVar19 = lVar19 + -1;
              pfVar18 = pfVar18 + 1;
            } while (lVar19 != 0);
          }
        }
        else if ((int)uVar8 < (int)uVar4) {
          uVar8 = uVar28;
          if ((int)uVar28 < 2) {
            uVar8 = 1;
          }
          if (0.0 < __ptr_00[uVar27 * uVar28]) {
            bVar14 = true;
          }
          if (1 < (int)uVar28) {
            if ((int)uVar28 < 9) {
              uVar20 = 1;
            }
            else {
              pauVar24 = (undefined (*) [16])((long)__ptr_00 + lVar25 * (ulong)uVar28 + 0x14);
              uVar34 = 0;
              uVar42 = 0;
              uVar21 = (ulong)uVar8 - 1;
              uVar23 = uVar21 & 0xfffffffffffffff8;
              uVar20 = uVar23 | 1;
              uVar35 = uVar23;
              do {
                pauVar1 = pauVar24 + -1;
                auVar48 = *pauVar24;
                uVar35 = uVar35 - 8;
                pauVar24 = pauVar24 + 2;
                auVar46 = NEON_fcmgt(*pauVar1,0,4);
                auVar48 = NEON_fcmgt(auVar48,0,4);
                bVar31 = (byte)uVar34 | auVar46[0];
                bVar36 = (byte)(uVar34 >> 0x10) | auVar46[4];
                bVar37 = (byte)(uVar34 >> 0x20) | auVar46[8];
                bVar38 = (byte)(uVar34 >> 0x30) | auVar46[12];
                uVar34 = (ulong)CONCAT16(bVar38,(uint6)CONCAT14(bVar37,(uint)CONCAT12(bVar36,(ushort
                                                  )bVar31)));
                bVar39 = (byte)uVar42 | auVar48[0];
                bVar43 = (byte)(uVar42 >> 0x10) | auVar48[4];
                bVar44 = (byte)(uVar42 >> 0x20) | auVar48[8];
                bVar45 = (byte)(uVar42 >> 0x30) | auVar48[12];
                uVar42 = (ulong)CONCAT16(bVar45,(uint6)CONCAT14(bVar44,(uint)CONCAT12(bVar43,(ushort
                                                  )bVar39)));
              } while (uVar35 != 0);
              uVar35 = NEON_cmlt(CONCAT26((ushort)(bVar45 | bVar38) << 0xf,
                                          CONCAT24((ushort)(bVar44 | bVar37) << 0xf,
                                                   CONCAT22((ushort)(bVar43 | bVar36) << 0xf,
                                                            (ushort)(bVar39 | bVar31) << 0xf))),0,2)
              ;
              uVar32 = NEON_addv(uVar35 & uVar13,2);
              if ((uVar32 & 0xf) != 0) {
                bVar14 = true;
              }
              if (uVar21 == uVar23) goto LAB_0057ef54;
            }
            lVar19 = uVar8 - uVar20;
            pfVar18 = (float *)((long)__ptr_00 + lVar25 * (ulong)uVar28 + uVar20 * 4);
            do {
              if (0.0 < *pfVar18) {
                bVar14 = true;
              }
              lVar19 = lVar19 + -1;
              pfVar18 = pfVar18 + 1;
            } while (lVar19 != 0);
          }
        }
        else {
          uVar29 = uVar4;
          if ((int)uVar4 <= (int)uVar8) {
            uVar29 = uVar8;
          }
          uVar35 = 0;
          do {
            uVar8 = (uint)(uVar35 >> 5) & 0x7ffffff;
            iVar9 = iVar11;
            if ((int)(uVar8 + 1) <= iVar11) {
              iVar9 = uVar8 + 1;
            }
            if (0.0 < __ptr_00[uVar27 * (long)(int)uVar28 + uVar35]) {
              iVar2 = uVar8 - 1;
              if (iVar11 <= (int)(uVar8 - 1)) {
                iVar2 = iVar11;
              }
              iVar5 = 0;
              if (0x1f < uVar35) {
                iVar5 = iVar2;
              }
              if (iVar5 <= iVar9) {
                iVar30 = iVar22 * uVar4 + iVar5;
                iVar2 = ~uVar29 + uVar4;
                do {
                  memset((void *)((long)pfVar17 + (long)iVar30),1,(ulong)(uint)(iVar9 - iVar5) + 1);
                  bVar14 = iVar2 != -1;
                  iVar2 = iVar2 + 1;
                  iVar30 = iVar30 + iVar22;
                } while (bVar14);
                uVar28 = *__ptr;
              }
              bVar14 = true;
            }
            uVar35 = uVar35 + 1;
          } while ((long)uVar35 < (long)(int)uVar28);
          uVar29 = __ptr[1];
        }
      }
LAB_0057ef54:
      uVar27 = uVar27 + 1;
      lVar25 = lVar25 + 4;
    } while ((long)uVar27 < (long)(int)uVar29);
    local_80 = CONCAT44(local_80._4_4_,iVar22);
    if (bVar14) {
      local_88 = pfVar17;
      pfVar18 = (float *)calloc(__nmemb,4);
      if (pfVar18 == (float *)0x0) {
        uVar26 = 0;
        goto LAB_0057f524;
      }
      local_80 = local_80 & 0xffffffff;
      local_98 = pfVar18;
      b6_rows(uVar29,uVar28,smooth_rows,&local_b0);
      local_80 = CONCAT44(1,(undefined4)local_80);
      b6_rows(__ptr[1],*__ptr,smooth_rows,&local_b0);
    }
    else {
      pfVar18 = (float *)0x0;
      local_88 = pfVar17;
    }
  }
  sVar6 = 0;
  if (pfVar17 != (float *)0x0) {
    sVar6 = sVar16;
  }
  free(pfVar17);
  if (bVar15 && bVar12) {
    __ptr_01 = (void *)b9_sky_rim(__ptr);
    if (__nmemb == 0) {
      fVar49 = 0.0;
      goto LAB_0057f48c;
    }
    if (__ptr_01 == (void *)0x0) goto LAB_0057f344;
    fVar49 = 0.0;
    fVar33 = 0.0;
    sVar16 = 0;
    uVar28 = 0;
    do {
      uVar29 = *(uint *)((long)__ptr_01 + sVar16 * 4);
      fVar40 = (float)(ulong)(uVar29 & 0xff) / 128.0;
      fVar47 = (float)(ulong)(uVar29 >> 8 & 0xff) / 128.0;
      fVar41 = __ptr_00[sVar16];
      if (__ptr_00[sVar16] <= fVar40) {
        fVar41 = fVar40;
      }
      fVar40 = (float)(ulong)(uVar29 >> 0x10 & 0xff) / 128.0;
      if (fVar41 <= fVar47) {
        fVar41 = fVar47;
      }
      if (fVar41 <= fVar40) {
        fVar41 = fVar40;
      }
      if (0.003 < fVar41) {
        uVar28 = uVar28 + 1;
        if (fVar49 <= fVar41) {
          fVar49 = fVar41;
        }
        fVar33 = fVar33 + fVar41;
      }
      sVar16 = sVar16 + 1;
    } while (__nmemb != sVar16);
LAB_0057f3a4:
    if (uVar28 == 0) goto LAB_0057f48c;
    lVar25 = 0;
    do {
      fVar40 = 1.0;
      fVar41 = (float)(ulong)((uint)lVar25 & 0xff) * 16.06275;
      iVar22 = (int)fVar41;
      if (iVar22 < 0x1000) {
        fVar40 = *(float *)(&RICH_DECODE + (long)iVar22 * 4) +
                 (fVar41 - (float)iVar22) *
                 (*(float *)(&DAT_0055d804 + (long)iVar22 * 4) -
                 *(float *)(&RICH_DECODE + (long)iVar22 * 4));
      }
      local_4b0[lVar25] = fVar40;
      lVar25 = lVar25 + 1;
    } while (lVar25 != 0x100);
    local_4c0 = local_4b0;
    local_4e8 = __ptr;
    pfStack_4e0 = __ptr_00;
    local_4d8 = param_3;
    local_4d0 = param_4;
    uStack_4cc = param_5;
    local_4c8 = param_6;
    iStack_4c4 = param_7;
    pvStack_4b8 = __ptr_01;
    b6_rows(param_5,param_4,apply_rows,&local_4e8);
    if (param_9 != (undefined8 *)0x0) {
      *(undefined4 *)param_9 = 1;
      *(uint *)((long)param_9 + 4) = uVar28;
      *(float *)(param_9 + 1) = fVar49;
      fVar33 = fVar33 / (float)(ulong)uVar28;
      goto LAB_0057f4a4;
    }
  }
  else {
    if (__nmemb != 0) {
LAB_0057f344:
      fVar49 = 0.0;
      fVar33 = 0.0;
      uVar28 = 0;
      pfVar17 = __ptr_00;
      sVar16 = __nmemb;
      do {
        fVar41 = *pfVar17;
        if (0.003 < fVar41) {
          uVar28 = uVar28 + 1;
          if (fVar49 <= fVar41) {
            fVar49 = fVar41;
          }
          fVar33 = fVar33 + fVar41;
        }
        sVar16 = sVar16 - 1;
        pfVar17 = pfVar17 + 1;
      } while (sVar16 != 0);
      __ptr_01 = (void *)0x0;
      goto LAB_0057f3a4;
    }
    fVar49 = 0.0;
    __ptr_01 = (void *)0x0;
LAB_0057f48c:
    if (param_9 != (undefined8 *)0x0) {
      fVar33 = 0.0;
      *(float *)(param_9 + 1) = fVar49;
      *param_9 = DAT_00100aa0;
LAB_0057f4a4:
      *(float *)((long)param_9 + 0xc) = fVar33;
      *(int *)(param_9 + 2) = param_7;
      *(uint *)((long)param_9 + 0x14) = (uint)(param_2 != (uint *)0x0);
      lVar25 = 0xf;
      if (pfVar18 != (float *)0x0) {
        lVar25 = 0x13;
      }
      *(int *)(param_9 + 3) = param_8;
      if (param_2 == (uint *)0x0) {
        lVar19 = 0;
      }
      else {
        lVar19 = 7;
        if (*(long *)(param_2 + 8) != 0) {
          lVar19 = 0xb;
        }
      }
      lVar7 = 8;
      if (0.0 >= param_1 || (!bVar15 || !bVar12)) {
        lVar7 = 0;
      }
      param_9[4] = sVar6 + (lVar25 + lVar7 + (ulong)(__ptr_01 != (void *)0x0) * 4 + lVar19) *
                           __nmemb;
    }
  }
  free(__ptr_01);
  uVar26 = 1;
  pfVar17 = __ptr_00;
  __ptr_00 = pfVar18;
LAB_0057f524:
  free(pfVar17);
  free(__ptr_00);
  free(*(void **)(__ptr + 4));
  free(*(void **)(__ptr + 6));
  free(*(void **)(__ptr + 8));
  free(__ptr);
  return uVar26;
}



/* 0057f594 b12_guard */

void b12_guard(float param_1)

{
  float fVar1;
  float fVar2;
  
  fVar2 = 0.0;
  if (((uint)param_1 & 0x7fffffff) < 0x7f800000) {
    fVar2 = 0.0;
    if (0.0 <= param_1) {
      fVar2 = param_1;
    }
    fVar1 = 1.0;
    if (fVar2 <= 1.0) {
      fVar1 = fVar2;
    }
    fVar1 = fVar1 + -0.35 + fVar1 + -0.35;
    fVar2 = 0.0;
    if (0.0 <= fVar1) {
      fVar2 = fVar1;
    }
    fVar1 = 1.0;
    if (fVar2 <= 1.0) {
      fVar1 = fVar2;
    }
    fVar2 = 1.0 - fVar1 * fVar1 * (3.0 - (fVar1 + fVar1));
  }
  guard_impl(fVar2);
  return;
}



/* 0057f604 b4_m3_grade */

undefined4 b4_m3_grade(long param_1,uint param_2,uint param_3,int param_4)

{
  byte bVar1;
  int iVar2;
  long lVar3;
  undefined4 uVar4;
  ulong uVar5;
  byte *pbVar6;
  ulong uVar7;
  byte *pbVar8;
  uint uVar9;
  float fVar10;
  float fVar11;
  float fVar12;
  byte local_110 [256];
  
  uVar4 = 0;
  if (((((int)param_3 < 0x8001) && ((int)param_2 < 0x8001)) && (param_1 != 0)) &&
     (((0 < (int)param_2 && (0 < (int)param_3)) &&
      (((int)(param_2 * 4) <= param_4 && ((ulong)param_3 * (ulong)param_2 < 0x4c4b401)))))) {
    uVar5 = 0;
    do {
      fVar10 = (float)(uVar5 & 0xffffffff) / 255.0;
      if (fVar10 <= 0.06) {
        lVar3 = 0;
      }
      else if (fVar10 <= 0.16) {
        lVar3 = 1;
      }
      else if (fVar10 <= 0.32) {
        lVar3 = 2;
      }
      else if (fVar10 <= 0.5) {
        lVar3 = 3;
      }
      else if (fVar10 <= 0.68) {
        lVar3 = 4;
      }
      else if (fVar10 <= 0.82) {
        lVar3 = 5;
      }
      else if (fVar10 <= 0.93) {
        lVar3 = 6;
      }
      else {
        lVar3 = 7;
      }
      iVar2 = (int)(((float)(&DAT_0055d7dc)[lVar3] +
                    ((fVar10 - (float)(&DAT_0055d7b8)[lVar3]) /
                    ((float)(&DAT_0055d7bc)[lVar3] - (float)(&DAT_0055d7b8)[lVar3])) *
                    ((float)(&DAT_0055d7e0)[lVar3] - (float)(&DAT_0055d7dc)[lVar3])) * 255.0 + 0.5);
      if (0xfe < iVar2) {
        iVar2 = 0xff;
      }
      local_110[uVar5] = (byte)iVar2 & ((byte)(iVar2 >> 0x1f) ^ 0xff);
      uVar5 = uVar5 + 1;
    } while (uVar5 != 0x100);
    uVar5 = 0;
    pbVar8 = (byte *)(param_1 + 2);
    uVar7 = (ulong)param_2;
    pbVar6 = pbVar8;
    do {
      do {
        fVar10 = (float)NEON_ucvtf((uint)pbVar8[-2]);
        fVar11 = (float)NEON_ucvtf((uint)pbVar8[-1]);
        fVar12 = (float)NEON_ucvtf((uint)*pbVar8);
        uVar9 = (uint)(fVar10 * 0.2126 + fVar11 * 0.7152 + fVar12 * 0.0722 + 0.5);
        if (0xfe < (int)uVar9) {
          uVar9 = 0xff;
        }
        uVar7 = uVar7 - 1;
        bVar1 = local_110[uVar9 & ((int)uVar9 >> 0x1f ^ 0xffffffffU)];
        *pbVar8 = bVar1;
        pbVar8[-1] = bVar1;
        pbVar8[-2] = bVar1;
        pbVar8 = pbVar8 + 4;
      } while (uVar7 != 0);
      uVar5 = uVar5 + 1;
      pbVar8 = pbVar6 + param_4;
      uVar7 = (ulong)param_2;
      pbVar6 = pbVar8;
    } while (uVar5 != param_3);
    uVar4 = 1;
  }
  return uVar4;
}



/* 0057f868 snapshot_rows */

void snapshot_rows(int **param_1,int param_2,int param_3)

{
  long lVar1;
  long lVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  int iVar6;
  int iVar7;
  int iVar8;
  float fVar9;
  bool bVar10;
  int iVar11;
  byte bVar12;
  int *piVar13;
  int iVar14;
  long lVar15;
  long lVar16;
  long lVar17;
  byte *pbVar18;
  byte *pbVar19;
  int *piVar20;
  int *piVar21;
  long lVar22;
  long lVar23;
  float fVar24;
  float fVar25;
  float fVar26;
  float fVar27;
  float fVar28;
  float fVar29;
  float fVar30;
  float fVar31;
  
  if (param_2 < param_3) {
    piVar20 = *param_1;
    bVar10 = *(int *)((long)param_1 + 0x1c) != 0;
    fVar29 = 0.2289746;
    if (bVar10) {
      fVar29 = 0.2126;
    }
    iVar11 = *piVar20;
    fVar30 = 0.07928691;
    fVar9 = 0.6917385;
    if (bVar10) {
      fVar30 = 0.0722;
      fVar9 = 0.7152;
    }
    if (0 < iVar11) {
      fVar31 = 1.0;
      iVar3 = *(int *)((long)param_1 + 0x14);
      iVar4 = *(int *)(param_1 + 3);
      piVar13 = param_1[1];
      piVar21 = param_1[4];
      lVar22 = (long)param_2;
      do {
        lVar1 = lVar22 + 1;
        if (0 < iVar11) {
          lVar23 = 0;
          do {
            iVar5 = piVar20[1];
            lVar2 = lVar23 + 1;
            iVar7 = 0;
            if (iVar5 != 0) {
              iVar7 = (iVar3 * (int)lVar22) / iVar5;
            }
            iVar8 = 0;
            if (iVar5 != 0) {
              iVar8 = (iVar3 * (int)lVar1) / iVar5;
            }
            if (iVar7 < iVar8) {
              iVar5 = param_1[5][lVar23];
              lVar16 = (long)iVar5;
              iVar6 = param_1[5][lVar2];
              if (iVar5 < iVar6) {
                lVar15 = (long)iVar7;
                iVar14 = 0;
                if (*(long *)(piVar20 + 8) == 0) {
                  fVar24 = 0.0;
                  fVar25 = 0.0;
                  fVar26 = 0.0;
                  lVar17 = iVar6 - lVar16;
                  pbVar19 = (byte *)((long)piVar13 + (long)iVar4 * (long)iVar7 + lVar16 * 4 + 2);
                  lVar16 = lVar17;
                  pbVar18 = pbVar19;
                  do {
                    do {
                      lVar16 = lVar16 + -1;
                      fVar26 = (float)piVar21[pbVar19[-2]] + fVar26;
                      fVar25 = (float)piVar21[pbVar19[-1]] + fVar25;
                      fVar24 = (float)piVar21[*pbVar19] + fVar24;
                      pbVar19 = pbVar19 + 4;
                    } while (lVar16 != 0);
                    lVar15 = lVar15 + 1;
                    iVar14 = (iVar6 - iVar5) + iVar14;
                    pbVar19 = pbVar18 + iVar4;
                    lVar16 = lVar17;
                    pbVar18 = pbVar19;
                  } while (lVar15 != iVar8);
                  goto LAB_0057fb78;
                }
                fVar24 = 0.0;
                fVar25 = 0.0;
                fVar26 = 0.0;
                fVar28 = 1.0;
                lVar17 = iVar6 - lVar16;
                pbVar19 = (byte *)((long)piVar13 + (long)iVar4 * (long)iVar7 + lVar16 * 4 + 2);
                lVar16 = lVar17;
                pbVar18 = pbVar19;
                do {
                  do {
                    fVar26 = (float)piVar21[pbVar19[-2]] + fVar26;
                    fVar25 = (float)piVar21[pbVar19[-1]] + fVar25;
                    fVar24 = (float)piVar21[*pbVar19] + fVar24;
                    fVar27 = fVar29 * (float)piVar21[pbVar19[-2]] +
                             fVar9 * (float)piVar21[pbVar19[-1]] + fVar30 * (float)piVar21[*pbVar19]
                    ;
                    if (fVar27 <= fVar28) {
                      fVar28 = fVar27;
                    }
                    lVar16 = lVar16 + -1;
                    pbVar19 = pbVar19 + 4;
                  } while (lVar16 != 0);
                  lVar15 = lVar15 + 1;
                  iVar14 = (iVar6 - iVar5) + iVar14;
                  pbVar19 = pbVar18 + iVar4;
                  lVar16 = lVar17;
                  pbVar18 = pbVar19;
                } while (lVar15 != iVar8);
                fVar28 = fVar28 + 0.004;
              }
              else {
                iVar14 = 0;
                fVar24 = 0.0;
                fVar25 = 0.0;
                fVar26 = 0.0;
LAB_0057fb78:
                fVar28 = 1.004;
              }
              fVar27 = (float)iVar14;
            }
            else {
              fVar25 = 0.0;
              fVar24 = 0.0;
              fVar28 = 1.004;
              fVar26 = 0.0;
              fVar27 = 0.0;
            }
            fVar26 = fVar26 / fVar27;
            lVar23 = lVar23 + lVar22 * iVar11;
            fVar25 = fVar25 / fVar27;
            fVar24 = fVar24 / fVar27;
            fVar27 = log2f(fVar29 * fVar26 + fVar9 * fVar25 + fVar30 * fVar24 + 0.004);
            lVar16 = *(long *)(piVar20 + 8);
            *(float *)(*(long *)(piVar20 + 4) + lVar23 * 4) = fVar27;
            if (lVar16 != 0) {
              fVar28 = log2f(fVar28);
              *(float *)(lVar16 + lVar23 * 4) = fVar28;
            }
            fVar28 = 0.0;
            if (0.0 <= fVar26) {
              fVar28 = fVar26;
            }
            fVar26 = fVar31;
            if (fVar28 <= 1.0) {
              fVar26 = fVar28;
            }
            iVar11 = (int)(fVar26 * 16384.0);
            if (iVar11 < 0x4000) {
              iVar11 = (int)((*(float *)(&RICH_ENCODE + (long)iVar11 * 4) +
                             (fVar26 * 16384.0 - (float)iVar11) *
                             (*(float *)(&DAT_00561808 + (long)iVar11 * 4) -
                             *(float *)(&RICH_ENCODE + (long)iVar11 * 4))) * 255.0 + 0.5);
              if (0xfe < iVar11) {
                iVar11 = 0xff;
              }
              bVar12 = (byte)iVar11 & ((byte)(iVar11 >> 0x1f) ^ 0xff);
            }
            else {
              bVar12 = 0xff;
            }
            lVar23 = lVar23 * 3;
            *(byte *)(*(long *)(piVar20 + 6) + lVar23) = bVar12;
            fVar28 = 0.0;
            if (0.0 <= fVar25) {
              fVar28 = fVar25;
            }
            fVar25 = fVar31;
            if (fVar28 <= 1.0) {
              fVar25 = fVar28;
            }
            iVar11 = (int)(fVar25 * 16384.0);
            if (iVar11 < 0x4000) {
              iVar11 = (int)((*(float *)(&RICH_ENCODE + (long)iVar11 * 4) +
                             (fVar25 * 16384.0 - (float)iVar11) *
                             (*(float *)(&DAT_00561808 + (long)iVar11 * 4) -
                             *(float *)(&RICH_ENCODE + (long)iVar11 * 4))) * 255.0 + 0.5);
              if (0xfe < iVar11) {
                iVar11 = 0xff;
              }
              bVar12 = (byte)iVar11 & ((byte)(iVar11 >> 0x1f) ^ 0xff);
            }
            else {
              bVar12 = 0xff;
            }
            fVar28 = 0.0;
            if (0.0 <= fVar24) {
              fVar28 = fVar24;
            }
            *(byte *)(*(long *)(piVar20 + 6) + lVar23 + 1) = bVar12;
            fVar24 = fVar31;
            if (fVar28 <= 1.0) {
              fVar24 = fVar28;
            }
            iVar11 = (int)(fVar24 * 16384.0);
            if (iVar11 < 0x4000) {
              iVar11 = (int)((*(float *)(&RICH_ENCODE + (long)iVar11 * 4) +
                             (fVar24 * 16384.0 - (float)iVar11) *
                             (*(float *)(&DAT_00561808 + (long)iVar11 * 4) -
                             *(float *)(&RICH_ENCODE + (long)iVar11 * 4))) * 255.0 + 0.5);
              if (0xfe < iVar11) {
                iVar11 = 0xff;
              }
              bVar12 = (byte)iVar11 & ((byte)(iVar11 >> 0x1f) ^ 0xff);
            }
            else {
              bVar12 = 0xff;
            }
            *(byte *)(*(long *)(piVar20 + 6) + lVar23 + 2) = bVar12;
            iVar11 = *piVar20;
            lVar23 = lVar2;
          } while (lVar2 < iVar11);
        }
        lVar22 = lVar1;
      } while (lVar1 != param_3);
    }
  }
  return;
}



/* 0057fd40 detect_rows */

void detect_rows(long *param_1,int param_2,int param_3)

{
  uint uVar1;
  uint uVar2;
  byte *pbVar3;
  byte *pbVar4;
  byte *pbVar5;
  int iVar6;
  int iVar7;
  uint uVar8;
  int iVar9;
  int iVar10;
  int iVar11;
  uint uVar12;
  int iVar13;
  int iVar14;
  uint uVar15;
  uint uVar16;
  uint uVar17;
  int iVar18;
  uint uVar19;
  uint uVar20;
  bool bVar21;
  bool bVar22;
  bool bVar23;
  bool bVar24;
  uint uVar25;
  int iVar26;
  long lVar27;
  uint uVar28;
  uint uVar29;
  uint *puVar30;
  ulong uVar31;
  long lVar32;
  long lVar33;
  uint uVar34;
  long lVar35;
  long lVar36;
  long lVar37;
  long lVar38;
  long lVar39;
  ulong uVar40;
  long lVar41;
  int iVar42;
  ulong uVar43;
  long lVar44;
  ulong uVar45;
  float fVar46;
  float fVar47;
  float fVar48;
  float fVar49;
  float fVar50;
  float fVar51;
  float fVar52;
  float fVar53;
  float fVar54;
  float fVar55;
  float fVar56;
  float fVar57;
  float fVar58;
  undefined8 uVar59;
  float fVar60;
  float fVar61;
  float fVar62;
  float fVar63;
  float fVar64;
  undefined8 uVar65;
  float fVar66;
  undefined8 uVar67;
  float fVar68;
  undefined8 uVar69;
  float fVar70;
  float fVar71;
  float fVar72;
  float fVar73;
  float fVar74;
  float fVar75;
  uint local_c8;
  uint local_c4;
  
  puVar30 = (uint *)param_1[1];
  uVar12 = puVar30[1];
  iVar18 = uVar12 - 2;
  iVar7 = param_2 + -0x2c;
  if (iVar18 <= param_2 + -0x2c) {
    iVar7 = iVar18;
  }
  iVar11 = 2;
  if (0x2d < param_2) {
    iVar11 = iVar7;
  }
  iVar7 = param_3 + 0x2c;
  if (iVar18 <= param_3 + 0x2c) {
    iVar7 = iVar18;
  }
  iVar18 = 2;
  if (param_3 + 0x2a < 0 == SCARRY4(param_3,0x2a)) {
    iVar18 = iVar7;
  }
  if (iVar11 < iVar18) {
    iVar7 = *(int *)(param_1 + 4);
    uVar8 = *puVar30;
    fVar46 = 0.58;
    if (iVar7 != 0) {
      fVar46 = 0.28;
    }
    if (4 < (int)uVar8) {
      iVar9 = *(int *)((long)param_1 + 0x24);
      lVar33 = param_1[2];
      lVar27 = (long)iVar11;
      lVar35 = *param_1;
      lVar39 = *(long *)(puVar30 + 4);
      uVar34 = iVar11 * uVar8 + 2;
      uVar29 = iVar11 * uVar8 * 3 + 6;
      do {
        uVar43 = 2;
        local_c8 = uVar29;
        local_c4 = uVar34;
        do {
          lVar32 = lVar27 * (ulong)uVar8 + uVar43;
          fVar53 = *(float *)(lVar39 + lVar32 * 4);
          if ((-5.2 <= fVar53 && fVar53 == -0.07 || -5.2 <= fVar53 && fVar53 < -0.07) &&
             (lVar41 = *(long *)(puVar30 + 8), fVar53 - *(float *)(lVar41 + lVar32 * 4) <= 0.7)) {
            lVar32 = 0;
            do {
              iVar11 = (&DAT_00571828)[lVar32];
              iVar13 = (&DAT_00571808)[lVar32];
              iVar26 = (int)lVar27;
              uVar19 = iVar26 - iVar11;
              uVar28 = iVar26 + iVar11 * -2;
              iVar42 = (int)uVar43;
              uVar20 = iVar42 - iVar13;
              uVar16 = uVar19 | uVar20;
              uVar25 = iVar42 + iVar13 * -2;
              bVar22 = false;
              if ((int)uVar19 < (int)uVar12) {
                bVar22 = (int)(uVar16 + 1) < 0;
              }
              bVar21 = uVar16 != 0xffffffff;
              lVar36 = (long)(int)(uVar20 + uVar19 * uVar8);
              bVar22 = bVar22 == ((int)uVar19 < (int)uVar12 && SCARRY4(uVar16,1));
              bVar23 = false;
              if (((int)uVar19 < (int)uVar12 && bVar21) && bVar22) {
                bVar23 = (int)(uVar8 - uVar20) < 0;
              }
              uVar16 = uVar28 | uVar25;
              if (((((int)uVar12 <= (int)uVar19 || !bVar21) || !bVar22) || uVar8 == uVar20) ||
                  bVar23 != ((((int)uVar19 < (int)uVar12 && bVar21) && bVar22) &&
                            SBORROW4(uVar8,uVar20))) {
                lVar36 = -1;
              }
              lVar38 = (long)(int)(uVar25 + uVar28 * uVar8);
              bVar22 = false;
              if ((int)uVar28 < (int)uVar12) {
                bVar22 = (int)(uVar16 + 1) < 0;
              }
              bVar21 = uVar16 != 0xffffffff;
              fVar54 = *(float *)(lVar41 + lVar36 * 4);
              bVar22 = bVar22 == ((int)uVar28 < (int)uVar12 && SCARRY4(uVar16,1));
              bVar23 = false;
              if (((int)uVar28 < (int)uVar12 && bVar21) && bVar22) {
                bVar23 = (int)(uVar8 - uVar25) < 0;
              }
              if (((((int)uVar12 <= (int)uVar28 || !bVar21) || !bVar22) || uVar8 == uVar25) ||
                  bVar23 != ((((int)uVar28 < (int)uVar12 && bVar21) && bVar22) &&
                            SBORROW4(uVar8,uVar25))) {
                lVar38 = -1;
              }
              fVar55 = *(float *)(lVar41 + lVar38 * 4);
              if (fVar55 <= fVar54) {
                fVar54 = fVar55;
              }
              if (0.78 <= fVar53 - fVar54) {
                fVar54 = 0.0;
                iVar14 = iVar11 * 6;
                iVar6 = iVar13 * -6;
                uVar16 = iVar14 + iVar42;
                uVar1 = iVar6 + iVar26;
                uVar17 = uVar1 | uVar16;
                uVar15 = uVar16 + uVar1 * uVar8;
                bVar22 = false;
                if ((int)uVar1 < (int)uVar12) {
                  bVar22 = (int)(uVar17 + 1) < 0;
                }
                bVar21 = uVar17 != 0xffffffff;
                uVar2 = iVar14 + uVar20;
                bVar22 = bVar22 == ((int)uVar1 < (int)uVar12 && SCARRY4(uVar17,1));
                bVar23 = false;
                if (((int)uVar1 < (int)uVar12 && bVar21) && bVar22) {
                  bVar23 = (int)(uVar8 - uVar16) < 0;
                }
                if (((((int)uVar12 <= (int)uVar1 || !bVar21) || !bVar22) || uVar8 == uVar16) ||
                    bVar23 != ((((int)uVar1 < (int)uVar12 && bVar21) && bVar22) &&
                              SBORROW4(uVar8,uVar16))) {
                  uVar15 = 0xffffffff;
                }
                if (((((int)uVar2 < (int)uVar8) &&
                     (uVar16 = iVar6 + uVar19, -1 < (int)(uVar16 | uVar2))) &&
                    ((int)uVar16 < (int)uVar12)) &&
                   ((-1 < (int)uVar15 && (uVar2 = uVar2 + uVar16 * uVar8, -1 < (int)uVar2)))) {
                  fVar56 = *(float *)(lVar39 + (ulong)uVar15 * 4);
                  fVar47 = fVar56 - fVar53;
                  fVar55 = -fVar47;
                  if (0.0 <= fVar47) {
                    fVar55 = fVar47;
                  }
                  if (fVar55 < 0.45) {
                    uVar16 = iVar14 + uVar25;
                    if ((((int)uVar16 < (int)uVar8) &&
                        (uVar1 = iVar6 + uVar28, -1 < (int)(uVar1 | uVar16))) &&
                       ((int)uVar1 < (int)uVar12)) {
                      uVar16 = uVar16 + uVar1 * uVar8;
                      fVar54 = *(float *)(lVar41 + (ulong)uVar2 * 4);
                      if ((-1 < (int)uVar16) &&
                         (fVar55 = *(float *)(lVar41 + (ulong)uVar16 * 4), fVar55 <= fVar54)) {
                        fVar54 = fVar55;
                      }
                    }
                    else {
                      fVar54 = *(float *)(lVar41 + (ulong)uVar2 * 4);
                    }
                    fVar55 = ((fVar56 - fVar54) + -0.55) / 0.6;
                    fVar54 = 0.0;
                    if (0.0 <= fVar55) {
                      fVar54 = fVar55;
                    }
                    fVar55 = 1.0;
                    if (fVar54 <= 1.0) {
                      fVar55 = fVar54;
                    }
                    fVar54 = fVar55 * fVar55 * (3.0 - (fVar55 + fVar55)) * 0.25 + 0.0;
                  }
                }
                iVar6 = iVar11 * 3;
                iVar14 = iVar13 * -3;
                uVar16 = iVar6 + iVar42;
                uVar1 = iVar14 + iVar26;
                uVar17 = uVar1 | uVar16;
                uVar15 = uVar16 + uVar1 * uVar8;
                bVar22 = false;
                if ((int)uVar1 < (int)uVar12) {
                  bVar22 = (int)(uVar17 + 1) < 0;
                }
                bVar21 = uVar17 != 0xffffffff;
                uVar2 = iVar6 + uVar20;
                bVar22 = bVar22 == ((int)uVar1 < (int)uVar12 && SCARRY4(uVar17,1));
                bVar23 = false;
                if (((int)uVar1 < (int)uVar12 && bVar21) && bVar22) {
                  bVar23 = (int)(uVar8 - uVar16) < 0;
                }
                if (((((int)uVar12 <= (int)uVar1 || !bVar21) || !bVar22) || uVar8 == uVar16) ||
                    bVar23 != ((((int)uVar1 < (int)uVar12 && bVar21) && bVar22) &&
                              SBORROW4(uVar8,uVar16))) {
                  uVar15 = 0xffffffff;
                }
                fVar55 = 0.0;
                if (((((int)uVar2 < (int)uVar8) &&
                     (uVar16 = iVar14 + uVar19, -1 < (int)(uVar16 | uVar2))) &&
                    ((int)uVar16 < (int)uVar12)) &&
                   ((-1 < (int)uVar15 && (uVar2 = uVar2 + uVar16 * uVar8, -1 < (int)uVar2)))) {
                  fVar57 = *(float *)(lVar39 + (ulong)uVar15 * 4);
                  fVar56 = fVar57 - fVar53;
                  fVar47 = -fVar56;
                  if (0.0 <= fVar56) {
                    fVar47 = fVar56;
                  }
                  if (fVar47 < 0.45) {
                    uVar16 = iVar6 + uVar25;
                    if ((((int)uVar16 < (int)uVar8) &&
                        (uVar1 = iVar14 + uVar28, -1 < (int)(uVar1 | uVar16))) &&
                       ((int)uVar1 < (int)uVar12)) {
                      uVar16 = uVar16 + uVar1 * uVar8;
                      fVar47 = *(float *)(lVar41 + (ulong)uVar2 * 4);
                      if ((-1 < (int)uVar16) &&
                         (fVar56 = *(float *)(lVar41 + (ulong)uVar16 * 4), fVar56 <= fVar47)) {
                        fVar47 = fVar56;
                      }
                    }
                    else {
                      fVar47 = *(float *)(lVar41 + (ulong)uVar2 * 4);
                    }
                    fVar56 = ((fVar57 - fVar47) + -0.55) / 0.6;
                    fVar47 = fVar55;
                    if (0.0 <= fVar56) {
                      fVar47 = fVar56;
                    }
                    fVar56 = 1.0;
                    if (fVar47 <= 1.0) {
                      fVar56 = fVar47;
                    }
                    fVar54 = fVar54 + fVar56 * fVar56 * (3.0 - (fVar56 + fVar56)) * 0.25;
                  }
                }
                iVar14 = iVar11 * -3;
                iVar6 = iVar13 * 3;
                uVar16 = iVar6 + iVar26;
                uVar1 = iVar14 + iVar42;
                uVar17 = uVar1 + uVar16 * uVar8;
                uVar2 = uVar16 | uVar1;
                uVar15 = iVar14 + uVar20;
                bVar22 = false;
                if ((int)uVar16 < (int)uVar12) {
                  bVar22 = (int)(uVar2 + 1) < 0;
                }
                bVar21 = uVar2 != 0xffffffff;
                bVar22 = bVar22 == ((int)uVar16 < (int)uVar12 && SCARRY4(uVar2,1));
                bVar23 = false;
                if (((int)uVar16 < (int)uVar12 && bVar21) && bVar22) {
                  bVar23 = (int)(uVar8 - uVar1) < 0;
                }
                if (((((int)uVar12 <= (int)uVar16 || !bVar21) || !bVar22) || uVar8 == uVar1) ||
                    bVar23 != ((((int)uVar16 < (int)uVar12 && bVar21) && bVar22) &&
                              SBORROW4(uVar8,uVar1))) {
                  uVar17 = 0xffffffff;
                }
                if (((((int)uVar15 < (int)uVar8) &&
                     (uVar16 = iVar6 + uVar19, -1 < (int)(uVar16 | uVar15))) &&
                    ((int)uVar16 < (int)uVar12)) &&
                   ((-1 < (int)uVar17 && (uVar15 = uVar15 + uVar16 * uVar8, -1 < (int)uVar15)))) {
                  fVar57 = *(float *)(lVar39 + (ulong)uVar17 * 4);
                  fVar56 = fVar57 - fVar53;
                  fVar47 = -fVar56;
                  if (0.0 <= fVar56) {
                    fVar47 = fVar56;
                  }
                  if (fVar47 < 0.45) {
                    uVar16 = iVar14 + uVar25;
                    if ((((int)uVar16 < (int)uVar8) &&
                        (uVar1 = iVar6 + uVar28, -1 < (int)(uVar1 | uVar16))) &&
                       ((int)uVar1 < (int)uVar12)) {
                      uVar16 = uVar16 + uVar1 * uVar8;
                      fVar47 = *(float *)(lVar41 + (ulong)uVar15 * 4);
                      if ((-1 < (int)uVar16) &&
                         (fVar56 = *(float *)(lVar41 + (ulong)uVar16 * 4), fVar56 <= fVar47)) {
                        fVar47 = fVar56;
                      }
                    }
                    else {
                      fVar47 = *(float *)(lVar41 + (ulong)uVar15 * 4);
                    }
                    fVar56 = ((fVar57 - fVar47) + -0.55) / 0.6;
                    fVar47 = fVar55;
                    if (0.0 <= fVar56) {
                      fVar47 = fVar56;
                    }
                    fVar56 = 1.0;
                    if (fVar47 <= 1.0) {
                      fVar56 = fVar47;
                    }
                    fVar54 = fVar54 + fVar56 * fVar56 * (3.0 - (fVar56 + fVar56)) * 0.25;
                  }
                }
                iVar6 = iVar11 * -6;
                iVar14 = iVar13 * 6;
                uVar16 = iVar6 + iVar42;
                uVar1 = iVar14 + iVar26;
                uVar17 = uVar1 | uVar16;
                uVar15 = uVar16 + uVar1 * uVar8;
                bVar22 = false;
                if ((int)uVar1 < (int)uVar12) {
                  bVar22 = (int)(uVar17 + 1) < 0;
                }
                bVar21 = uVar17 != 0xffffffff;
                uVar20 = iVar6 + uVar20;
                bVar22 = bVar22 == ((int)uVar1 < (int)uVar12 && SCARRY4(uVar17,1));
                bVar23 = false;
                if (((int)uVar1 < (int)uVar12 && bVar21) && bVar22) {
                  bVar23 = (int)(uVar8 - uVar16) < 0;
                }
                if (((((int)uVar12 <= (int)uVar1 || !bVar21) || !bVar22) || uVar8 == uVar16) ||
                    bVar23 != ((((int)uVar1 < (int)uVar12 && bVar21) && bVar22) &&
                              SBORROW4(uVar8,uVar16))) {
                  uVar15 = 0xffffffff;
                }
                if (((((int)uVar20 < (int)uVar8) &&
                     (uVar19 = iVar14 + uVar19, -1 < (int)(uVar19 | uVar20))) &&
                    ((int)uVar19 < (int)uVar12)) &&
                   ((-1 < (int)uVar15 && (uVar20 = uVar20 + uVar19 * uVar8, -1 < (int)uVar20)))) {
                  fVar57 = *(float *)(lVar39 + (ulong)uVar15 * 4);
                  fVar56 = fVar57 - fVar53;
                  fVar47 = -fVar56;
                  if (0.0 <= fVar56) {
                    fVar47 = fVar56;
                  }
                  if (fVar47 < 0.45) {
                    uVar25 = iVar6 + uVar25;
                    if ((((int)uVar25 < (int)uVar8) &&
                        (uVar28 = iVar14 + uVar28, -1 < (int)(uVar28 | uVar25))) &&
                       ((int)uVar28 < (int)uVar12)) {
                      uVar25 = uVar25 + uVar28 * uVar8;
                      fVar47 = *(float *)(lVar41 + (ulong)uVar20 * 4);
                      if ((-1 < (int)uVar25) &&
                         (fVar56 = *(float *)(lVar41 + (ulong)uVar25 * 4), fVar56 <= fVar47)) {
                        fVar47 = fVar56;
                      }
                    }
                    else {
                      fVar47 = *(float *)(lVar41 + (ulong)uVar20 * 4);
                    }
                    fVar56 = ((fVar57 - fVar47) + -0.55) / 0.6;
                    fVar47 = fVar55;
                    if (0.0 <= fVar56) {
                      fVar47 = fVar56;
                    }
                    fVar56 = 1.0;
                    if (fVar47 <= 1.0) {
                      fVar56 = fVar47;
                    }
                    fVar54 = fVar54 + fVar56 * fVar56 * (3.0 - (fVar56 + fVar56)) * 0.25;
                  }
                }
                if (0.42 <= fVar54) {
                  iVar14 = iVar13 + uVar8 * iVar11;
                  lVar36 = 0;
                  bVar22 = true;
                  do {
                    bVar21 = bVar22;
                    iVar6 = (&DAT_00571848)[lVar36 * 3];
                    iVar10 = (&DAT_00571850)[lVar36 * 3];
                    uVar25 = iVar42 + iVar6 * iVar13;
                    uVar28 = iVar42 + (&DAT_0057184c)[lVar36 * 3] * iVar13;
                    uVar20 = iVar6 * iVar11 + iVar26;
                    uVar16 = uVar20 | uVar25;
                    uVar19 = uVar25 + uVar20 * uVar8;
                    bVar22 = false;
                    if ((int)uVar20 < (int)uVar12) {
                      bVar22 = (int)(uVar16 + 1) < 0;
                    }
                    bVar23 = uVar16 != 0xffffffff;
                    uVar1 = (&DAT_0057184c)[lVar36 * 3] * iVar11 + iVar26;
                    bVar22 = bVar22 == ((int)uVar20 < (int)uVar12 && SCARRY4(uVar16,1));
                    bVar24 = false;
                    if (((int)uVar20 < (int)uVar12 && bVar23) && bVar22) {
                      bVar24 = (int)(uVar8 - uVar25) < 0;
                    }
                    uVar16 = uVar1 | uVar28;
                    if (((((int)uVar12 <= (int)uVar20 || !bVar23) || !bVar22) || uVar8 == uVar25) ||
                        bVar24 != ((((int)uVar20 < (int)uVar12 && bVar23) && bVar22) &&
                                  SBORROW4(uVar8,uVar25))) {
                      uVar19 = 0xffffffff;
                    }
                    uVar20 = uVar28 + uVar1 * uVar8;
                    bVar22 = false;
                    if ((int)uVar1 < (int)uVar12) {
                      bVar22 = (int)(uVar16 + 1) < 0;
                    }
                    bVar23 = uVar16 != 0xffffffff;
                    uVar25 = iVar42 + iVar10 * iVar13;
                    bVar22 = bVar22 == ((int)uVar1 < (int)uVar12 && SCARRY4(uVar16,1));
                    bVar24 = false;
                    if (((int)uVar1 < (int)uVar12 && bVar23) && bVar22) {
                      bVar24 = (int)(uVar8 - uVar28) < 0;
                    }
                    uVar16 = iVar10 * iVar11 + iVar26;
                    if (((((int)uVar12 <= (int)uVar1 || !bVar23) || !bVar22) || uVar8 == uVar28) ||
                        bVar24 != ((((int)uVar1 < (int)uVar12 && bVar23) && bVar22) &&
                                  SBORROW4(uVar8,uVar28))) {
                      uVar20 = 0xffffffff;
                    }
                    uVar1 = uVar16 | uVar25;
                    uVar28 = uVar25 + uVar16 * uVar8;
                    bVar22 = false;
                    if ((int)uVar16 < (int)uVar12) {
                      bVar22 = (int)(uVar1 + 1) < 0;
                    }
                    bVar23 = uVar1 != 0xffffffff;
                    bVar22 = bVar22 == ((int)uVar16 < (int)uVar12 && SCARRY4(uVar1,1));
                    bVar24 = false;
                    if (((int)uVar16 < (int)uVar12 && bVar23) && bVar22) {
                      bVar24 = (int)(uVar8 - uVar25) < 0;
                    }
                    if (((((int)uVar12 <= (int)uVar16 || !bVar23) || !bVar22) || uVar8 == uVar25) ||
                        bVar24 != ((((int)uVar16 < (int)uVar12 && bVar23) && bVar22) &&
                                  SBORROW4(uVar8,uVar25))) {
                      uVar28 = 0xffffffff;
                    }
                    if (((-1 < (int)uVar19) && (-1 < (int)uVar20)) && (-1 < (int)uVar28)) {
                      fVar56 = *(float *)(lVar39 + (ulong)uVar20 * 4);
                      fVar58 = *(float *)(lVar39 + (ulong)uVar28 * 4);
                      fVar57 = *(float *)(lVar39 + (ulong)uVar19 * 4);
                      fVar47 = fVar56;
                      if (fVar58 <= fVar56) {
                        fVar47 = fVar58;
                      }
                      fVar62 = fVar56;
                      if (fVar56 <= fVar58) {
                        fVar62 = fVar58;
                      }
                      fVar63 = fVar57;
                      if (fVar47 <= fVar57) {
                        fVar63 = fVar47;
                      }
                      fVar47 = fVar57;
                      if (fVar57 <= fVar62) {
                        fVar47 = fVar62;
                      }
                      if (fVar47 - fVar63 <= 0.32) {
                        lVar38 = (ulong)uVar19 * 3;
                        lVar44 = *(long *)(puVar30 + 6);
                        pbVar3 = (byte *)(lVar44 + lVar38);
                        pbVar4 = (byte *)(lVar44 + (ulong)uVar28 * 3);
                        fVar60 = (float)NEON_ucvtf((uint)pbVar3[1]);
                        fVar61 = (float)NEON_ucvtf((uint)pbVar3[2]);
                        fVar64 = (float)NEON_ucvtf((uint)*pbVar3);
                        fVar68 = (float)NEON_ucvtf((uint)pbVar4[1]);
                        fVar70 = (float)NEON_ucvtf((uint)pbVar4[2]);
                        fVar71 = (float)NEON_ucvtf((uint)*pbVar4);
                        fVar62 = fVar60;
                        if (fVar60 <= fVar61) {
                          fVar62 = fVar61;
                        }
                        fVar66 = fVar64;
                        if (fVar64 <= fVar62) {
                          fVar66 = fVar62;
                        }
                        fVar62 = fVar68;
                        if (fVar68 <= fVar70) {
                          fVar62 = fVar70;
                        }
                        fVar66 = fVar66 + 8.0;
                        fVar74 = fVar71;
                        if (fVar71 <= fVar62) {
                          fVar74 = fVar62;
                        }
                        fVar74 = fVar74 + 8.0;
                        fVar64 = fVar64 / fVar66 - fVar71 / fVar74;
                        fVar60 = fVar60 / fVar66 - fVar68 / fVar74;
                        fVar62 = -fVar64;
                        if (0.0 <= fVar64) {
                          fVar62 = fVar64;
                        }
                        fVar64 = -fVar60;
                        if (0.0 <= fVar60) {
                          fVar64 = fVar60;
                        }
                        fVar61 = fVar61 / fVar66 - fVar70 / fVar74;
                        fVar60 = -fVar61;
                        if (0.0 <= fVar61) {
                          fVar60 = fVar61;
                        }
                        if (fVar60 + fVar64 + fVar62 + 0.0 <= 0.2) {
                          uVar25 = iVar42 + (&DAT_00100a40)[lVar36] * iVar13;
                          if ((((int)uVar25 < (int)uVar8) &&
                              (uVar28 = iVar26 + (&DAT_00100a40)[lVar36] * iVar11,
                              -1 < (int)(uVar28 | uVar25))) &&
                             (((int)uVar28 < (int)uVar12 &&
                              (uVar25 = uVar25 + uVar28 * uVar8, -1 < (int)uVar25)))) {
                            fVar60 = ((fVar58 - fVar57) / (float)(iVar10 - iVar6)) * (float)iVar6;
                            fVar62 = -0.35;
                            if (-0.35 <= fVar60) {
                              fVar62 = fVar60;
                            }
                            fVar60 = 0.35;
                            if (fVar62 <= 0.35) {
                              fVar60 = fVar62;
                            }
                            fVar62 = fVar56 + (fVar57 + fVar58) * -0.5;
                            fVar58 = fVar47;
                            if (fVar47 <= fVar57 - fVar60) {
                              fVar58 = fVar57 - fVar60;
                            }
                            fVar60 = -fVar62;
                            if (0.0 <= fVar62) {
                              fVar60 = fVar62;
                            }
                            fVar60 = (fVar60 + -0.04) / 0.08;
                            fVar63 = ((fVar47 - fVar63) + -0.16) / 0.16;
                            fVar62 = 0.0;
                            fVar47 = 0.0;
                            if (0.0 <= fVar60) {
                              fVar47 = fVar60;
                            }
                            fVar60 = 1.0;
                            if (fVar47 <= 1.0) {
                              fVar60 = fVar47;
                            }
                            fVar47 = 0.0;
                            if (0.0 <= fVar63) {
                              fVar47 = fVar63;
                            }
                            fVar63 = 1.0;
                            if (fVar47 <= 1.0) {
                              fVar63 = fVar47;
                            }
                            if (iVar9 != 0) {
                              if (iVar7 == 0) {
                                pbVar3 = (byte *)(lVar44 + (ulong)uVar20 + (ulong)uVar20 * 2);
                                fVar64 = (float)NEON_ucvtf((uint)*pbVar3);
                                uVar59 = NEON_ucvtf((ulong)CONCAT14(pbVar3[2],(uint)pbVar3[1]),4);
                                fVar61 = (float)((ulong)uVar59 >> 0x20);
                                fVar62 = (float)uVar59;
                                fVar47 = fVar62;
                                if (fVar62 == fVar61 || fVar61 > fVar62) {
                                  fVar47 = fVar61;
                                }
                                fVar68 = fVar62;
                                if (fVar61 <= fVar62) {
                                  fVar68 = fVar61;
                                }
                                fVar70 = fVar64;
                                if (fVar64 <= fVar47) {
                                  fVar70 = fVar47;
                                }
                                fVar47 = fVar64;
                                if (fVar68 <= fVar64) {
                                  fVar47 = fVar68;
                                }
                                fVar68 = (fVar58 + (float)DAT_00100a38) / (float)DAT_00100b18;
                                fVar70 = (((fVar70 + 1.0) - fVar47) / (fVar70 + 1.0) +
                                         (float)((ulong)DAT_00100a38 >> 0x20)) /
                                         (float)((ulong)DAT_00100b18 >> 0x20);
                                uVar67 = NEON_fmov(0x3f800000,4);
                                fVar47 = ((fVar62 - fVar61) + (float)DAT_00100b20) /
                                         (float)DAT_00100b00;
                                fVar62 = ((fVar61 - fVar64) + (float)((ulong)DAT_00100b20 >> 0x20))
                                         / (float)((ulong)DAT_00100b00 >> 0x20);
                                uVar59 = NEON_fcmlt(CONCAT44(fVar70,fVar68),0,4);
                                uVar59 = CONCAT17((byte)((uint)fVar70 >> 0x18) &
                                                  ~(byte)((ulong)uVar59 >> 0x38),
                                                  CONCAT16((byte)((uint)fVar70 >> 0x10) &
                                                           ~(byte)((ulong)uVar59 >> 0x30),
                                                           CONCAT15((byte)((uint)fVar70 >> 8) &
                                                                    ~(byte)((ulong)uVar59 >> 0x28),
                                                                    CONCAT14(SUB41(fVar70,0) &
                                                                             ~(byte)((ulong)uVar59
                                                                                    >> 0x20),
                                                                             CONCAT13((byte)((uint)
                                                  fVar68 >> 0x18) & ~(byte)((ulong)uVar59 >> 0x18),
                                                  CONCAT12((byte)((uint)fVar68 >> 0x10) &
                                                           ~(byte)((ulong)uVar59 >> 0x10),
                                                           CONCAT11((byte)((uint)fVar68 >> 8) &
                                                                    ~(byte)((ulong)uVar59 >> 8),
                                                                    SUB41(fVar68,0) & ~(byte)uVar59)
                                                          ))))));
                                uVar65 = NEON_fcmgt(uVar59,uVar67,4);
                                uVar69 = NEON_fcmlt(CONCAT44(fVar62,fVar47),0,4);
                                uVar65 = NEON_bit(uVar59,uVar67,uVar65,1);
                                uVar59 = CONCAT17((byte)((uint)fVar62 >> 0x18) &
                                                  ~(byte)((ulong)uVar69 >> 0x38),
                                                  CONCAT16((byte)((uint)fVar62 >> 0x10) &
                                                           ~(byte)((ulong)uVar69 >> 0x30),
                                                           CONCAT15((byte)((uint)fVar62 >> 8) &
                                                                    ~(byte)((ulong)uVar69 >> 0x28),
                                                                    CONCAT14(SUB41(fVar62,0) &
                                                                             ~(byte)((ulong)uVar69
                                                                                    >> 0x20),
                                                                             CONCAT13((byte)((uint)
                                                  fVar47 >> 0x18) & ~(byte)((ulong)uVar69 >> 0x18),
                                                  CONCAT12((byte)((uint)fVar47 >> 0x10) &
                                                           ~(byte)((ulong)uVar69 >> 0x10),
                                                           CONCAT11((byte)((uint)fVar47 >> 8) &
                                                                    ~(byte)((ulong)uVar69 >> 8),
                                                                    SUB41(fVar47,0) & ~(byte)uVar69)
                                                          ))))));
                                uVar69 = NEON_fmov(0x40400000,4);
                                fVar61 = (float)uVar65;
                                fVar64 = (float)((ulong)uVar65 >> 0x20);
                                uVar65 = NEON_fcmgt(uVar59,uVar67,4);
                                fVar68 = (float)((ulong)uVar69 >> 0x20);
                                uVar59 = NEON_bit(uVar59,uVar67,uVar65,1);
                                fVar47 = (float)uVar59;
                                fVar62 = (float)((ulong)uVar59 >> 0x20);
                                fVar61 = (1.0 - fVar64 * fVar64 * (fVar68 - (fVar64 + fVar64))) *
                                         fVar61 * fVar61 * ((float)uVar69 - (fVar61 + fVar61)) *
                                         0.65;
                                fVar62 = (1.0 - fVar47 * fVar47 *
                                                ((float)uVar69 - (fVar47 + fVar47))) *
                                         fVar62 * fVar62 * (fVar68 - (fVar62 + fVar62));
                                if (fVar62 <= fVar61) {
                                  fVar62 = fVar61;
                                }
                              }
                              else {
                                fVar62 = 0.6;
                              }
                              fVar61 = ((*(float *)(lVar39 + (ulong)uVar25 * 4) - fVar58) + -0.015)
                                       / 0.04;
                              fVar47 = 0.0;
                              if (0.0 <= fVar61) {
                                fVar47 = fVar61;
                              }
                              fVar61 = 1.0;
                              if (fVar47 <= 1.0) {
                                fVar61 = fVar47;
                              }
                              fVar62 = fVar62 * fVar61 * fVar61 * (3.0 - (fVar61 + fVar61));
                            }
                            uVar16 = (&DAT_00100b40)[lVar36];
                            uVar45 = 0;
                            fVar47 = (float)uVar16 * 0.65;
                            pbVar3 = (byte *)(lVar44 + (ulong)(uVar20 * 3));
                            lVar36 = lVar27;
                            uVar40 = uVar43;
                            uVar25 = local_c8;
                            uVar28 = local_c4;
                            do {
                              if ((((long)(ulong)uVar8 <= (long)uVar40) ||
                                  ((int)((uint)lVar36 | (uint)uVar40) < 0)) ||
                                 (((int)uVar12 <= lVar36 ||
                                  (((int)uVar28 < 0 ||
                                   (fVar61 = *(float *)(lVar39 + (ulong)uVar28 * 4),
                                   fVar61 < fVar58 + -0.45)))))) break;
                              if ((param_2 <= lVar36) && (lVar36 < param_3)) {
                                pbVar4 = (byte *)(lVar44 + (ulong)uVar25);
                                fVar68 = (float)NEON_ucvtf((uint)pbVar3[1]);
                                fVar70 = (float)NEON_ucvtf((uint)pbVar3[2]);
                                fVar71 = (float)NEON_ucvtf((uint)*pbVar3);
                                fVar66 = (float)NEON_ucvtf((uint)pbVar4[1]);
                                fVar74 = (float)NEON_ucvtf((uint)pbVar4[2]);
                                fVar72 = (float)NEON_ucvtf((uint)*pbVar4);
                                fVar64 = fVar66;
                                if (fVar66 <= fVar74) {
                                  fVar64 = fVar74;
                                }
                                fVar75 = fVar72;
                                if (fVar72 <= fVar64) {
                                  fVar75 = fVar64;
                                }
                                fVar64 = fVar68;
                                if (fVar68 <= fVar70) {
                                  fVar64 = fVar70;
                                }
                                fVar75 = fVar75 + 8.0;
                                fVar49 = fVar71;
                                if (fVar71 <= fVar64) {
                                  fVar49 = fVar64;
                                }
                                fVar49 = fVar49 + 8.0;
                                fVar66 = fVar66 / fVar75 - fVar68 / fVar49;
                                fVar71 = fVar72 / fVar75 - fVar71 / fVar49;
                                fVar64 = 0.0;
                                fVar68 = -fVar71;
                                if (0.0 <= fVar71) {
                                  fVar68 = fVar71;
                                }
                                fVar71 = -fVar66;
                                if (0.0 <= fVar66) {
                                  fVar71 = fVar66;
                                }
                                fVar66 = fVar74 / fVar75 - fVar70 / fVar49;
                                fVar70 = -fVar66;
                                if (0.0 <= fVar66) {
                                  fVar70 = fVar66;
                                }
                                uVar31 = (ulong)uVar28;
                                fVar70 = (fVar70 + fVar71 + fVar68 + 0.0 + -0.12) / 0.23;
                                fVar71 = (fVar61 - fVar58) + -0.018;
                                fVar68 = 0.0;
                                if (0.0 <= fVar70) {
                                  fVar68 = fVar70;
                                }
                                fVar70 = 1.0;
                                if (fVar68 <= 1.0) {
                                  fVar70 = fVar68;
                                }
                                fVar68 = 0.0;
                                if (0.0 <= fVar71) {
                                  fVar68 = fVar71;
                                }
                                fVar71 = fVar46;
                                if (fVar68 <= fVar46) {
                                  fVar71 = fVar68;
                                }
                                fVar68 = 1.0 - fVar70 * fVar70 * (3.0 - (fVar70 + fVar70));
                                if (lVar35 != 0) {
                                  lVar37 = *(long *)(lVar35 + 0x10);
                                  fVar72 = *(float *)(lVar37 + uVar31 * 4);
                                  fVar70 = *(float *)(lVar37 + (ulong)uVar19 * 4);
                                  fVar74 = fVar72 - fVar70;
                                  fVar66 = -fVar74;
                                  if (0.0 <= fVar74) {
                                    fVar66 = fVar74;
                                  }
                                  if (fVar66 < 0.28) {
                                    fVar74 = *(float *)(lVar37 + (ulong)uVar20 * 4);
                                    fVar75 = fVar72 - fVar74;
                                    fVar66 = -fVar75;
                                    if (0.0 <= fVar75) {
                                      fVar66 = fVar75;
                                    }
                                    if (fVar66 < 0.28) {
                                      pbVar4 = (byte *)(*(long *)(lVar35 + 0x18) + (ulong)uVar25);
                                      pbVar5 = (byte *)(*(long *)(lVar35 + 0x18) + lVar38);
                                      fVar73 = (float)NEON_ucvtf((uint)pbVar4[1]);
                                      fVar66 = (float)NEON_ucvtf((uint)pbVar4[2]);
                                      fVar75 = (float)NEON_ucvtf((uint)*pbVar4);
                                      fVar49 = (float)NEON_ucvtf((uint)pbVar5[1]);
                                      fVar51 = (float)NEON_ucvtf((uint)pbVar5[2]);
                                      fVar52 = (float)NEON_ucvtf((uint)*pbVar5);
                                      fVar64 = fVar73;
                                      if (fVar73 <= fVar66) {
                                        fVar64 = fVar66;
                                      }
                                      fVar50 = fVar75;
                                      if (fVar75 <= fVar64) {
                                        fVar50 = fVar64;
                                      }
                                      fVar64 = fVar49;
                                      if (fVar49 <= fVar51) {
                                        fVar64 = fVar51;
                                      }
                                      fVar50 = fVar50 + 8.0;
                                      fVar48 = fVar52;
                                      if (fVar52 <= fVar64) {
                                        fVar48 = fVar64;
                                      }
                                      fVar48 = fVar48 + 8.0;
                                      fVar52 = fVar75 / fVar50 - fVar52 / fVar48;
                                      fVar49 = fVar73 / fVar50 - fVar49 / fVar48;
                                      fVar64 = 0.0;
                                      fVar75 = -fVar52;
                                      if (0.0 <= fVar52) {
                                        fVar75 = fVar52;
                                      }
                                      fVar51 = fVar66 / fVar50 - fVar51 / fVar48;
                                      fVar66 = -fVar49;
                                      if (0.0 <= fVar49) {
                                        fVar66 = fVar49;
                                      }
                                      fVar49 = -fVar51;
                                      if (0.0 <= fVar51) {
                                        fVar49 = fVar51;
                                      }
                                      if (fVar49 + fVar66 + fVar75 + 0.0 < 0.18) {
                                        fVar70 = fVar57 - fVar70;
                                        fVar74 = fVar56 - fVar74;
                                        if (fVar70 <= fVar74) {
                                          fVar70 = fVar74;
                                        }
                                        fVar64 = ((fVar61 - fVar72) - fVar70) + -0.045;
                                        fVar61 = 0.0;
                                        if (0.0 <= fVar64) {
                                          fVar61 = fVar64;
                                        }
                                        fVar64 = 0.62;
                                        if (fVar61 <= 0.62) {
                                          fVar64 = fVar61;
                                        }
                                        fVar64 = fVar68 * fVar54 * fVar64;
                                      }
                                    }
                                  }
                                }
                                fVar70 = ((float)(uVar45 & 0xffffffff) - fVar47) /
                                         (((float)uVar16 + 1.0) - fVar47);
                                fVar68 = (1.0 - fVar63 * fVar63 * (3.0 - (fVar63 + fVar63))) *
                                         fVar54 * (1.0 - fVar60 * fVar60 * (3.0 - (fVar60 + fVar60))
                                                  ) * fVar62 * fVar71 * fVar68;
                                fVar61 = fVar55;
                                if (0.0 <= fVar70) {
                                  fVar61 = fVar70;
                                }
                                fVar70 = 1.0;
                                if (fVar61 <= 1.0) {
                                  fVar70 = fVar61;
                                }
                                if (fVar64 <= fVar68) {
                                  fVar64 = fVar68;
                                }
                                fVar64 = (1.0 - fVar70 * fVar70 * (3.0 - (fVar70 + fVar70))) *
                                         fVar64;
                                fVar61 = *(float *)(lVar33 + uVar31 * 4);
                                if (fVar61 <= fVar64) {
                                  fVar61 = fVar64;
                                }
                                *(float *)(lVar33 + uVar31 * 4) = fVar61;
                              }
                              uVar45 = uVar45 + 1;
                              uVar25 = uVar25 + iVar14 * 3;
                              uVar28 = uVar28 + iVar14;
                              lVar36 = lVar36 + iVar11;
                              uVar40 = uVar40 + (long)iVar13;
                            } while ((uVar16 & ((int)uVar16 >> 0x1f ^ 0xffffffffU)) + 1 != uVar45);
                          }
                        }
                      }
                    }
                    lVar36 = 1;
                    bVar22 = false;
                  } while (bVar21);
                }
              }
              lVar32 = lVar32 + 1;
            } while (lVar32 != 8);
          }
          uVar43 = uVar43 + 1;
          local_c8 = local_c8 + 3;
          local_c4 = local_c4 + 1;
        } while (uVar43 != uVar8 - 2);
        lVar27 = lVar27 + 1;
        uVar29 = uVar29 + uVar8 * 3;
        uVar34 = uVar34 + uVar8;
      } while (lVar27 != iVar18);
    }
  }
  return;
}



/* 00580c48 smooth_rows */

void smooth_rows(long param_1,int param_2,int param_3)

{
  ulong uVar1;
  long lVar2;
  long lVar3;
  int iVar4;
  uint uVar5;
  long lVar6;
  uint uVar7;
  ulong uVar8;
  uint *puVar9;
  ulong uVar10;
  long lVar11;
  long lVar12;
  long lVar13;
  uint uVar14;
  int iVar15;
  ulong uVar16;
  long lVar17;
  long lVar18;
  long lVar19;
  long lVar20;
  long lVar21;
  long lVar22;
  long lVar23;
  float fVar24;
  float fVar25;
  float fVar26;
  float fVar27;
  
  iVar4 = *(int *)(param_1 + 0x34);
  lVar13 = 0x10;
  if (iVar4 != 0) {
    lVar13 = 0x18;
  }
  lVar12 = 0x18;
  if (iVar4 != 0) {
    lVar12 = 0x10;
  }
  if (param_2 < param_3) {
    puVar9 = *(uint **)(param_1 + 8);
    uVar10 = (ulong)*puVar9;
    if (0 < (int)*puVar9) {
      lVar11 = *(long *)(param_1 + lVar13);
      lVar13 = *(long *)(param_1 + lVar12);
      lVar12 = *(long *)(param_1 + 0x28);
      if (iVar4 == 0) {
        uVar16 = (ulong)param_2;
        lVar20 = uVar10 * 4;
        lVar17 = uVar16 * uVar10 * 4;
        lVar18 = (uVar16 - 3) * uVar10 * 4;
        lVar19 = lVar11 + lVar17;
        lVar13 = lVar13 + lVar17;
        lVar6 = lVar11 + lVar18;
        do {
          iVar15 = (int)uVar16;
          uVar8 = 0;
          iVar4 = iVar15 + 0x1f;
          if (-1 < iVar15) {
            iVar4 = iVar15;
          }
          lVar21 = uVar16 - 2;
          lVar2 = uVar16 + 1;
          lVar3 = uVar16 + 2;
          do {
            if ((lVar12 == 0) ||
               (*(char *)(lVar12 + (int)(*(int *)(param_1 + 0x30) * (iVar4 >> 5) +
                                        ((uint)uVar8 >> 5))) != '\0')) {
              lVar23 = lVar3;
              if ((long)uVar16 < 3) {
                fVar24 = 0.0;
                fVar25 = 0.0;
                fVar26 = 0.0;
                fVar27 = 0.0;
                if (1 < (long)uVar16) {
                  lVar22 = 0;
LAB_005811d8:
                  fVar26 = 0.0;
                  fVar24 = 0.0;
                  if (lVar22 < (int)puVar9[1]) goto LAB_005811fc;
                  goto LAB_0058122c;
                }
                if (0 < (long)uVar16) {
                  lVar22 = 0;
                  if ((long)(int)puVar9[1] < (long)uVar16) goto LAB_005812ec;
                  goto LAB_00581290;
                }
                if (-1 < (long)uVar16) goto LAB_005812ec;
                if (uVar16 == 0xffffffffffffffff) {
                  lVar22 = 0;
                  if (0 < (int)puVar9[1]) goto LAB_00581368;
                  goto LAB_00581398;
                }
                if (0xfffffffffffffffd < uVar16) {
                  lVar23 = 0;
                  if (0 < (int)puVar9[1]) goto LAB_005813e0;
                  goto LAB_00581410;
                }
                if ((0xfffffffffffffffc < uVar16) && (lVar23 = 0, 0 < (int)puVar9[1]))
                goto LAB_00581458;
              }
              else {
                fVar24 = 0.0;
                lVar22 = lVar21;
                if ((long)(uVar16 - 3) < (long)(int)puVar9[1]) {
                  fVar26 = *(float *)(*(long *)(puVar9 + 4) + lVar17 + uVar8 * 4) -
                           *(float *)(*(long *)(puVar9 + 4) + lVar18 + uVar8 * 4);
                  fVar24 = -fVar26;
                  if (0.0 <= fVar26) {
                    fVar24 = fVar26;
                  }
                  if (0.35 < fVar24) goto LAB_005811d8;
                  fVar26 = 1.0 / (fVar24 * fVar24 * 120.0 + 1.0);
                  fVar24 = fVar26 + 0.0;
                  fVar26 = fVar26 * *(float *)(lVar6 + uVar8 * 4) + 0.0;
                  uVar5 = puVar9[1];
                }
                else {
                  fVar26 = 0.0;
                  uVar5 = puVar9[1];
                }
                if (lVar21 < (int)uVar5) {
LAB_005811fc:
                  lVar22 = uVar8 + lVar22 * uVar10;
                  fVar27 = *(float *)(*(long *)(puVar9 + 4) + lVar17 + uVar8 * 4) -
                           *(float *)(*(long *)(puVar9 + 4) + lVar22 * 4);
                  fVar25 = -fVar27;
                  if (0.0 <= fVar27) {
                    fVar25 = fVar27;
                  }
                  if (0.35 < fVar25) goto LAB_0058122c;
                  fVar25 = 2.0 / (fVar25 * fVar25 * 120.0 + 1.0);
                  fVar24 = fVar24 + fVar25;
                  fVar26 = fVar26 + fVar25 * *(float *)(lVar11 + lVar22 * 4);
                  uVar5 = puVar9[1];
                }
                else {
LAB_0058122c:
                  uVar5 = puVar9[1];
                }
                lVar22 = uVar16 - 1;
                if ((long)uVar16 <= (long)(int)uVar5) {
LAB_00581290:
                  lVar22 = uVar8 + lVar22 * uVar10;
                  fVar27 = *(float *)(*(long *)(puVar9 + 4) + lVar17 + uVar8 * 4) -
                           *(float *)(*(long *)(puVar9 + 4) + lVar22 * 4);
                  fVar25 = -fVar27;
                  if (0.0 <= fVar27) {
                    fVar25 = fVar27;
                  }
                  if (fVar25 <= 0.35) {
                    fVar25 = 3.0 / (fVar25 * fVar25 * 120.0 + 1.0);
                    fVar24 = fVar24 + fVar25;
                    fVar26 = fVar26 + fVar25 * *(float *)(lVar11 + lVar22 * 4);
                  }
                }
LAB_005812ec:
                lVar22 = lVar2;
                if ((long)uVar16 < (long)(int)puVar9[1]) {
                  fVar27 = *(float *)(*(long *)(puVar9 + 4) + lVar17 + uVar8 * 4);
                  fVar27 = fVar27 - fVar27;
                  fVar25 = -fVar27;
                  if (0.0 <= fVar27) {
                    fVar25 = fVar27;
                  }
                  if (0.35 < fVar25) goto LAB_00581320;
                  fVar25 = 4.0 / (fVar25 * fVar25 * 120.0 + 1.0);
                  fVar24 = fVar24 + fVar25;
                  fVar26 = fVar26 + fVar25 * *(float *)(lVar19 + uVar8 * 4);
                  if (lVar2 < (int)puVar9[1]) goto LAB_00581368;
LAB_00581398:
                  if ((int)puVar9[1] <= lVar3) goto LAB_00581410;
LAB_005813e0:
                  lVar23 = uVar8 + lVar23 * uVar10;
                  fVar27 = *(float *)(*(long *)(puVar9 + 4) + lVar17 + uVar8 * 4) -
                           *(float *)(*(long *)(puVar9 + 4) + lVar23 * 4);
                  fVar25 = -fVar27;
                  if (0.0 <= fVar27) {
                    fVar25 = fVar27;
                  }
                  if (0.35 < fVar25) goto LAB_00581410;
                  fVar27 = 2.0 / (fVar25 * fVar25 * 120.0 + 1.0);
                  fVar25 = fVar24 + fVar27;
                  fVar27 = fVar26 + fVar27 * *(float *)(lVar11 + lVar23 * 4);
                  uVar5 = puVar9[1];
                }
                else {
LAB_00581320:
                  if ((int)puVar9[1] <= lVar2) goto LAB_00581398;
LAB_00581368:
                  lVar22 = uVar8 + lVar22 * uVar10;
                  fVar27 = *(float *)(*(long *)(puVar9 + 4) + lVar17 + uVar8 * 4) -
                           *(float *)(*(long *)(puVar9 + 4) + lVar22 * 4);
                  fVar25 = -fVar27;
                  if (0.0 <= fVar27) {
                    fVar25 = fVar27;
                  }
                  if (0.35 < fVar25) goto LAB_00581398;
                  fVar25 = 3.0 / (fVar25 * fVar25 * 120.0 + 1.0);
                  fVar24 = fVar24 + fVar25;
                  fVar26 = fVar26 + fVar25 * *(float *)(lVar11 + lVar22 * 4);
                  if (lVar3 < (int)puVar9[1]) goto LAB_005813e0;
LAB_00581410:
                  uVar5 = puVar9[1];
                  fVar25 = fVar24;
                  fVar27 = fVar26;
                }
                lVar23 = uVar16 + 3;
                fVar24 = fVar25;
                fVar26 = fVar27;
                if ((long)(uVar16 + 3) < (long)(int)uVar5) {
LAB_00581458:
                  fVar27 = fVar26;
                  fVar25 = fVar24;
                  lVar23 = uVar8 + lVar23 * uVar10;
                  fVar26 = *(float *)(*(long *)(puVar9 + 4) + lVar17 + uVar8 * 4) -
                           *(float *)(*(long *)(puVar9 + 4) + lVar23 * 4);
                  fVar24 = -fVar26;
                  if (0.0 <= fVar26) {
                    fVar24 = fVar26;
                  }
                  if (fVar24 <= 0.35) {
                    fVar24 = 1.0 / (fVar24 * fVar24 * 120.0 + 1.0);
                    fVar25 = fVar25 + fVar24;
                    fVar27 = fVar27 + fVar24 * *(float *)(lVar11 + lVar23 * 4);
                  }
                }
              }
              fVar27 = fVar27 / fVar25;
              if (fVar25 == 0.0) {
                fVar27 = 0.0;
              }
              *(float *)(lVar13 + uVar8 * 4) = fVar27;
            }
            uVar8 = uVar8 + 1;
          } while (uVar10 != uVar8);
          uVar16 = uVar16 + 1;
          lVar18 = lVar18 + lVar20;
          lVar6 = lVar6 + lVar20;
          lVar19 = lVar19 + lVar20;
          lVar13 = lVar13 + lVar20;
          lVar17 = lVar17 + lVar20;
        } while (uVar16 != (long)param_3);
      }
      else {
        uVar16 = (ulong)param_2;
        do {
          lVar19 = uVar16 * uVar10;
          uVar14 = (uint)uVar16;
          uVar5 = uVar14 + 0x1f;
          if (-1 < (int)uVar14) {
            uVar5 = uVar14;
          }
          uVar8 = 0;
          do {
            while ((uVar7 = (uint)uVar8, lVar12 == 0 ||
                   (*(char *)(lVar12 + (int)(*(int *)(param_1 + 0x30) * ((int)uVar5 >> 5) +
                                            (uVar7 >> 5))) != '\0'))) {
              fVar24 = 0.0;
              lVar6 = lVar19 + uVar8;
              if ((int)(uVar14 | (uint)(uVar8 - 3)) < 0) {
LAB_00580da8:
                fVar26 = 0.0;
              }
              else if ((long)uVar16 < (long)(int)puVar9[1]) {
                lVar18 = lVar19 + (uVar8 - 3);
                if (lVar18 < 0) goto LAB_00580da8;
                fVar25 = *(float *)(*(long *)(puVar9 + 4) + lVar6 * 4) -
                         *(float *)(*(long *)(puVar9 + 4) + lVar18 * 4);
                fVar26 = -fVar25;
                if (0.0 <= fVar25) {
                  fVar26 = fVar25;
                }
                if (0.35 < fVar26) goto LAB_00580dd4;
                fVar24 = 1.0 / (fVar26 * fVar26 * 120.0 + 1.0);
                fVar26 = fVar24 + 0.0;
                fVar24 = fVar24 * *(float *)(lVar11 + lVar18 * 4) + 0.0;
              }
              else {
LAB_00580dd4:
                fVar26 = 0.0;
              }
              if (((-1 < (int)(uVar14 | uVar7 - 2)) && ((long)uVar16 < (long)(int)puVar9[1])) &&
                 (lVar18 = lVar19 + (uVar8 - 2), -1 < lVar18)) {
                fVar27 = *(float *)(*(long *)(puVar9 + 4) + lVar6 * 4) -
                         *(float *)(*(long *)(puVar9 + 4) + lVar18 * 4);
                fVar25 = -fVar27;
                if (0.0 <= fVar27) {
                  fVar25 = fVar27;
                }
                if (fVar25 <= 0.35) {
                  fVar25 = 2.0 / (fVar25 * fVar25 * 120.0 + 1.0);
                  fVar26 = fVar26 + fVar25;
                  fVar24 = fVar24 + fVar25 * *(float *)(lVar11 + lVar18 * 4);
                }
              }
              if (((-1 < (int)(uVar14 | (uint)(uVar8 - 1))) && ((long)uVar16 < (long)(int)puVar9[1])
                  ) && (lVar18 = lVar19 + (uVar8 - 1), -1 < lVar18)) {
                fVar27 = *(float *)(*(long *)(puVar9 + 4) + lVar6 * 4) -
                         *(float *)(*(long *)(puVar9 + 4) + lVar18 * 4);
                fVar25 = -fVar27;
                if (0.0 <= fVar27) {
                  fVar25 = fVar27;
                }
                if (fVar25 <= 0.35) {
                  fVar25 = 3.0 / (fVar25 * fVar25 * 120.0 + 1.0);
                  fVar26 = fVar26 + fVar25;
                  fVar24 = fVar24 + fVar25 * *(float *)(lVar11 + lVar18 * 4);
                }
              }
              if (((-1 < (int)(uVar14 | uVar7)) && ((long)uVar16 < (long)(int)puVar9[1])) &&
                 (-1 < lVar6)) {
                fVar27 = *(float *)(*(long *)(puVar9 + 4) + lVar6 * 4);
                fVar27 = fVar27 - fVar27;
                fVar25 = -fVar27;
                if (0.0 <= fVar27) {
                  fVar25 = fVar27;
                }
                if (fVar25 <= 0.35) {
                  fVar25 = 4.0 / (fVar25 * fVar25 * 120.0 + 1.0);
                  fVar26 = fVar26 + fVar25;
                  fVar24 = fVar24 + fVar25 * *(float *)(lVar11 + lVar6 * 4);
                }
              }
              uVar1 = uVar8 + 1;
              if (((((long)uVar1 < (long)uVar10) && (-1 < (int)(uVar14 | (uint)uVar1))) &&
                  ((long)uVar16 < (long)(int)puVar9[1])) && (lVar18 = lVar19 + uVar1, -1 < lVar18))
              {
                fVar27 = *(float *)(*(long *)(puVar9 + 4) + lVar6 * 4) -
                         *(float *)(*(long *)(puVar9 + 4) + lVar18 * 4);
                fVar25 = -fVar27;
                if (0.0 <= fVar27) {
                  fVar25 = fVar27;
                }
                if (fVar25 <= 0.35) {
                  fVar25 = 3.0 / (fVar25 * fVar25 * 120.0 + 1.0);
                  fVar26 = fVar26 + fVar25;
                  fVar24 = fVar24 + fVar25 * *(float *)(lVar11 + lVar18 * 4);
                }
              }
              lVar18 = uVar8 + 2;
              if (((lVar18 < (long)uVar10) && (-1 < (int)(uVar14 | (uint)lVar18))) &&
                 (((long)uVar16 < (long)(int)puVar9[1] && (lVar18 = lVar19 + lVar18, -1 < lVar18))))
              {
                fVar27 = *(float *)(*(long *)(puVar9 + 4) + lVar6 * 4) -
                         *(float *)(*(long *)(puVar9 + 4) + lVar18 * 4);
                fVar25 = -fVar27;
                if (0.0 <= fVar27) {
                  fVar25 = fVar27;
                }
                if (fVar25 <= 0.35) {
                  fVar25 = 2.0 / (fVar25 * fVar25 * 120.0 + 1.0);
                  fVar26 = fVar26 + fVar25;
                  fVar24 = fVar24 + fVar25 * *(float *)(lVar11 + lVar18 * 4);
                }
              }
              lVar18 = uVar8 + 3;
              if (((lVar18 < (long)uVar10) && (-1 < (int)(uVar14 | (uint)lVar18))) &&
                 (((long)uVar16 < (long)(int)puVar9[1] && (lVar18 = lVar19 + lVar18, -1 < lVar18))))
              {
                fVar27 = *(float *)(*(long *)(puVar9 + 4) + lVar6 * 4) -
                         *(float *)(*(long *)(puVar9 + 4) + lVar18 * 4);
                fVar25 = -fVar27;
                if (0.0 <= fVar27) {
                  fVar25 = fVar27;
                }
                if (fVar25 <= 0.35) {
                  fVar25 = 1.0 / (fVar25 * fVar25 * 120.0 + 1.0);
                  fVar26 = fVar26 + fVar25;
                  fVar24 = fVar24 + fVar25 * *(float *)(lVar11 + lVar18 * 4);
                }
              }
              fVar24 = fVar24 / fVar26;
              if (fVar26 == 0.0) {
                fVar24 = 0.0;
              }
              *(float *)(lVar13 + lVar6 * 4) = fVar24;
              uVar8 = uVar1;
              if (uVar1 == uVar10) goto LAB_00580cc4;
            }
            uVar8 = uVar8 + 1;
          } while (uVar8 != uVar10);
LAB_00580cc4:
          uVar16 = uVar16 + 1;
        } while (uVar16 != (long)param_3);
      }
    }
  }
  return;
}



/* 00581518 apply_rows */

void apply_rows(int **param_1,int param_2,int param_3)

{
  int iVar1;
  int iVar2;
  int iVar3;
  int *piVar4;
  int *piVar5;
  uint uVar6;
  uint uVar7;
  int iVar8;
  int iVar9;
  int iVar10;
  float fVar11;
  bool bVar12;
  byte bVar13;
  int iVar14;
  int *piVar15;
  long lVar16;
  int iVar17;
  int iVar18;
  long lVar19;
  long lVar20;
  long lVar21;
  ulong uVar22;
  long lVar23;
  byte *pbVar24;
  byte *pbVar25;
  long lVar26;
  float fVar27;
  int iVar28;
  float fVar29;
  float fVar30;
  float fVar31;
  float fVar32;
  float fVar33;
  float fVar34;
  undefined8 uVar35;
  float fVar36;
  float fVar37;
  float fVar38;
  float fVar39;
  float fVar40;
  float fVar41;
  float fVar42;
  float fVar43;
  float fVar44;
  float fVar45;
  float fVar46;
  
  if (param_2 < param_3) {
    bVar12 = *(int *)((long)param_1 + 0x24) != 0;
    fVar38 = 0.2289746;
    if (bVar12) {
      fVar38 = 0.2126;
    }
    uVar6 = *(uint *)(param_1 + 3);
    fVar27 = 0.07928691;
    fVar11 = 0.6917385;
    if (bVar12) {
      fVar27 = 0.0722;
      fVar11 = 0.7152;
    }
    if (0 < (int)uVar6) {
      iVar8 = *(int *)(param_1 + 4);
      lVar19 = (long)param_2;
      piVar4 = *param_1;
      piVar5 = param_1[1];
      pbVar24 = (byte *)((long)param_1[2] + (long)iVar8 * (long)param_2 + 1);
      iVar28 = *(int *)((long)param_1 + 0x1c);
      do {
        uVar22 = 0;
        pbVar25 = pbVar24;
        do {
          iVar3 = *piVar4;
          iVar9 = piVar4[1] + -1;
          iVar10 = iVar3 + -1;
          fVar29 = (((float)(int)lVar19 + 0.5) * (float)piVar4[1]) / (float)iVar28 + -0.5;
          iVar17 = (int)fVar29;
          iVar14 = iVar17;
          if (iVar9 <= iVar17) {
            iVar14 = iVar9;
          }
          fVar31 = (((float)(uVar22 & 0xffffffff) + 0.5) * (float)iVar3) / (float)uVar6 + -0.5;
          iVar1 = 0;
          if (-1 < iVar17) {
            iVar1 = iVar14;
          }
          iVar18 = (int)fVar31;
          iVar14 = iVar18;
          if (iVar10 <= iVar18) {
            iVar14 = iVar10;
          }
          iVar2 = 0;
          if (-1 < iVar18) {
            iVar2 = iVar14;
          }
          if (iVar18 + 1 < iVar10) {
            iVar10 = iVar18 + 1;
          }
          iVar14 = 0;
          if (iVar18 + 1 < 0 == SCARRY4(iVar18,1)) {
            iVar14 = iVar10;
          }
          if (iVar17 + 1 < iVar9) {
            iVar9 = iVar17 + 1;
          }
          iVar10 = iVar1 * iVar3 + iVar2;
          iVar1 = iVar1 * iVar3 + iVar14;
          iVar18 = 0;
          if (iVar17 + 1 < 0 == SCARRY4(iVar17,1)) {
            iVar18 = iVar9;
          }
          fVar44 = (float)piVar5[iVar10];
          fVar43 = (float)piVar5[iVar1];
          lVar20 = (long)iVar10;
          lVar21 = (long)iVar1;
          iVar2 = iVar18 * iVar3 + iVar2;
          iVar14 = iVar18 * iVar3 + iVar14;
          fVar41 = (float)piVar5[iVar2];
          fVar40 = (float)piVar5[iVar14];
          lVar23 = (long)iVar2;
          lVar26 = (long)iVar14;
          if ((0.0005 <= fVar44 + fVar43 + fVar41 + fVar40) ||
             ((piVar15 = param_1[6], piVar15 != (int *)0x0 &&
              ((piVar15[lVar21] | piVar15[lVar20] | piVar15[lVar23] | piVar15[lVar26]) != 0)))) {
            piVar15 = param_1[5];
            fVar45 = (float)piVar15[pbVar25[-1]];
            fVar42 = (float)piVar15[*pbVar25];
            fVar39 = (float)piVar15[pbVar25[1]];
            fVar29 = fVar29 - (float)(int)(float)(int)fVar29;
            fVar31 = fVar31 - (float)(int)(float)(int)fVar31;
            fVar30 = log2f(fVar38 * fVar45 + fVar11 * fVar42 + fVar27 * fVar39 + 0.004);
            lVar16 = *(long *)(piVar4 + 4);
            fVar32 = fVar30 - *(float *)(lVar16 + lVar20 * 4);
            fVar46 = -fVar32;
            if (0.0 <= fVar32) {
              fVar46 = fVar32;
            }
            fVar34 = 1.0 - fVar31;
            fVar36 = 1.0 - fVar29;
            fVar33 = 0.0;
            fVar32 = 0.0;
            if (fVar46 <= 0.45) {
              fVar32 = (fVar36 * fVar34) / (fVar46 * fVar46 * 150.0 + 1.0);
              fVar33 = fVar32 + 0.0;
              fVar32 = fVar32 * fVar44 + 0.0;
            }
            fVar37 = fVar30 - *(float *)(lVar16 + lVar21 * 4);
            fVar44 = -fVar37;
            if (0.0 <= fVar37) {
              fVar44 = fVar37;
            }
            if (fVar44 <= 0.45) {
              fVar37 = (fVar36 * fVar31) / (fVar44 * fVar44 * 150.0 + 1.0);
              fVar33 = fVar33 + fVar37;
              fVar32 = fVar32 + fVar37 * fVar43;
            }
            fVar37 = fVar30 - *(float *)(lVar16 + lVar23 * 4);
            fVar43 = -fVar37;
            if (0.0 <= fVar37) {
              fVar43 = fVar37;
            }
            if (fVar43 <= 0.45) {
              fVar37 = (fVar29 * fVar34) / (fVar43 * fVar43 * 150.0 + 1.0);
              fVar33 = fVar33 + fVar37;
              fVar32 = fVar32 + fVar37 * fVar41;
            }
            fVar30 = fVar30 - *(float *)(lVar16 + lVar26 * 4);
            fVar41 = -fVar30;
            if (0.0 <= fVar30) {
              fVar41 = fVar30;
            }
            if (fVar41 <= 0.45) {
              fVar30 = (fVar29 * fVar31) / (fVar41 * fVar41 * 150.0 + 1.0);
              fVar33 = fVar33 + fVar30;
              fVar32 = fVar32 + fVar30 * fVar40;
            }
            if (1e-08 <= fVar33) {
              piVar15 = param_1[6];
              if (piVar15 == (int *)0x0) {
                fVar46 = 0.0;
                fVar30 = 0.0;
                fVar40 = 0.0;
              }
              else {
                if (fVar46 <= 0.28) {
                  uVar7 = piVar15[lVar20];
                  fVar30 = (fVar36 * fVar34) / (fVar46 * fVar46 * 150.0 + 1.0);
                  uVar35 = NEON_ucvtf(CONCAT44(uVar7 >> 8,uVar7) & 0xff000000ff,4);
                  fVar37 = fVar30 + 0.0;
                  fVar40 = fVar30 * (float)(ulong)(uVar7 >> 0x10 & 0xff) * 0.0078125 + 0.0;
                  fVar46 = (float)uVar35 * fVar30 * 0.0078125 + 0.0;
                  fVar30 = (float)((ulong)uVar35 >> 0x20) * fVar30 * 0.0078125 + 0.0;
                }
                else {
                  fVar46 = 0.0;
                  fVar30 = 0.0;
                  fVar40 = 0.0;
                  fVar37 = 0.0;
                }
                if (fVar44 <= 0.28) {
                  uVar7 = piVar15[lVar21];
                  fVar44 = (fVar36 * fVar31) / (fVar44 * fVar44 * 150.0 + 1.0);
                  uVar35 = NEON_ucvtf(CONCAT44(uVar7 >> 8,uVar7) & 0xff000000ff,4);
                  fVar37 = fVar37 + fVar44;
                  fVar40 = fVar44 * (float)(ulong)(uVar7 >> 0x10 & 0xff) * 0.0078125 + fVar40;
                  fVar46 = (float)uVar35 * fVar44 * 0.0078125 + fVar46;
                  fVar30 = (float)((ulong)uVar35 >> 0x20) * fVar44 * 0.0078125 + fVar30;
                }
                if (fVar43 <= 0.28) {
                  uVar7 = piVar15[lVar23];
                  fVar43 = (fVar29 * fVar34) / (fVar43 * fVar43 * 150.0 + 1.0);
                  uVar35 = NEON_ucvtf(CONCAT44(uVar7 >> 8,uVar7) & 0xff000000ff,4);
                  fVar37 = fVar37 + fVar43;
                  fVar40 = fVar43 * (float)(ulong)(uVar7 >> 0x10 & 0xff) * 0.0078125 + fVar40;
                  fVar46 = (float)uVar35 * fVar43 * 0.0078125 + fVar46;
                  fVar30 = (float)((ulong)uVar35 >> 0x20) * fVar43 * 0.0078125 + fVar30;
                }
                if (fVar41 <= 0.28) {
                  uVar7 = piVar15[lVar26];
                  fVar29 = (fVar29 * fVar31) / (fVar41 * fVar41 * 150.0 + 1.0);
                  uVar35 = NEON_ucvtf(CONCAT44(uVar7 >> 8,uVar7) & 0xff000000ff,4);
                  fVar37 = fVar37 + fVar29;
                  fVar40 = fVar29 * (float)(ulong)(uVar7 >> 0x10 & 0xff) * 0.0078125 + fVar40;
                  fVar46 = (float)uVar35 * fVar29 * 0.0078125 + fVar46;
                  fVar30 = (float)((ulong)uVar35 >> 0x20) * fVar29 * 0.0078125 + fVar30;
                }
                if (1e-08 < fVar37) {
                  fVar40 = fVar40 / fVar37;
                  fVar46 = fVar46 / fVar37;
                  fVar30 = fVar30 / fVar37;
                }
              }
              fVar32 = fVar32 / fVar33;
              fVar29 = fVar32;
              if (fVar32 <= fVar46) {
                fVar29 = fVar46;
              }
              fVar29 = exp2f(-fVar29);
              fVar45 = fVar45 * fVar29;
              fVar29 = 0.0;
              if (0.0 <= fVar45) {
                fVar29 = fVar45;
              }
              fVar31 = 1.0;
              if (fVar29 <= 1.0) {
                fVar31 = fVar29;
              }
              iVar14 = (int)(fVar31 * 16384.0);
              if (iVar14 < 0x4000) {
                iVar14 = (int)((*(float *)(&RICH_ENCODE + (long)iVar14 * 4) +
                               (fVar31 * 16384.0 - (float)iVar14) *
                               (*(float *)(&DAT_00561808 + (long)iVar14 * 4) -
                               *(float *)(&RICH_ENCODE + (long)iVar14 * 4))) * 255.0 + 0.5);
                if (0xfe < iVar14) {
                  iVar14 = 0xff;
                }
                bVar13 = (byte)iVar14 & ((byte)(iVar14 >> 0x1f) ^ 0xff);
              }
              else {
                bVar13 = 0xff;
              }
              pbVar25[-1] = bVar13;
              fVar29 = fVar32;
              if (fVar32 <= fVar30) {
                fVar29 = fVar30;
              }
              fVar29 = exp2f(-fVar29);
              fVar42 = fVar42 * fVar29;
              fVar29 = 0.0;
              if (0.0 <= fVar42) {
                fVar29 = fVar42;
              }
              fVar31 = 1.0;
              if (fVar29 <= 1.0) {
                fVar31 = fVar29;
              }
              iVar14 = (int)(fVar31 * 16384.0);
              if (iVar14 < 0x4000) {
                iVar14 = (int)((*(float *)(&RICH_ENCODE + (long)iVar14 * 4) +
                               (fVar31 * 16384.0 - (float)iVar14) *
                               (*(float *)(&DAT_00561808 + (long)iVar14 * 4) -
                               *(float *)(&RICH_ENCODE + (long)iVar14 * 4))) * 255.0 + 0.5);
                if (0xfe < iVar14) {
                  iVar14 = 0xff;
                }
                bVar13 = (byte)iVar14 & ((byte)(iVar14 >> 0x1f) ^ 0xff);
              }
              else {
                bVar13 = 0xff;
              }
              *pbVar25 = bVar13;
              if (fVar32 <= fVar40) {
                fVar32 = fVar40;
              }
              fVar29 = exp2f(-fVar32);
              fVar39 = fVar39 * fVar29;
              fVar29 = 0.0;
              if (0.0 <= fVar39) {
                fVar29 = fVar39;
              }
              fVar31 = 1.0;
              if (fVar29 <= 1.0) {
                fVar31 = fVar29;
              }
              iVar14 = (int)(fVar31 * 16384.0);
              if (iVar14 < 0x4000) {
                iVar14 = (int)((*(float *)(&RICH_ENCODE + (long)iVar14 * 4) +
                               (fVar31 * 16384.0 - (float)iVar14) *
                               (*(float *)(&DAT_00561808 + (long)iVar14 * 4) -
                               *(float *)(&RICH_ENCODE + (long)iVar14 * 4))) * 255.0 + 0.5);
                if (0xfe < iVar14) {
                  iVar14 = 0xff;
                }
                bVar13 = (byte)iVar14 & ((byte)(iVar14 >> 0x1f) ^ 0xff);
              }
              else {
                bVar13 = 0xff;
              }
              pbVar25[1] = bVar13;
            }
          }
          uVar22 = uVar22 + 1;
          pbVar25 = pbVar25 + 4;
        } while (uVar6 != uVar22);
        lVar19 = lVar19 + 1;
        pbVar24 = pbVar24 + iVar8;
      } while (lVar19 != param_3);
    }
  }
  return;
}



/* 00581d70 b12_soft_rim */

void b12_soft_rim(float param_1,uint *param_2,long param_3)

{
  undefined (*pauVar1) [16];
  int iVar2;
  int iVar3;
  int iVar4;
  uint uVar5;
  uint uVar6;
  ulong uVar7;
  uint uVar8;
  uint uVar9;
  uint uVar10;
  float fVar11;
  uint uVar12;
  bool bVar13;
  void *__ptr;
  void *__ptr_00;
  void *__ptr_01;
  float *pfVar14;
  long lVar15;
  ulong uVar16;
  undefined (*pauVar17) [16];
  float *pfVar18;
  ulong uVar19;
  undefined (*pauVar20) [16];
  ulong uVar21;
  int iVar22;
  size_t __nmemb;
  int iVar23;
  ulong uVar24;
  byte bVar25;
  ushort uVar26;
  byte bVar27;
  byte bVar28;
  byte bVar29;
  byte bVar30;
  byte bVar32;
  byte bVar33;
  byte bVar34;
  undefined auVar31 [16];
  undefined auVar35 [16];
  undefined auVar36 [16];
  undefined8 uVar38;
  undefined auVar37 [16];
  undefined auVar39 [16];
  void *local_d0;
  uint *local_b8;
  void *local_b0;
  void *local_a8;
  void *pvStack_a0;
  int local_98;
  undefined4 local_94;
  uint *local_90;
  void *pvStack_88;
  float local_80;
  
  if (param_2 == (uint *)0x0) {
    return;
  }
  if (*(long *)(param_2 + 4) == 0) {
    return;
  }
  if (param_3 == 0) {
    return;
  }
  if (*(long *)(param_2 + 6) == 0) {
    return;
  }
  uVar8 = *param_2;
  if ((int)uVar8 < 0x10) {
    return;
  }
  uVar9 = param_2[1];
  if ((int)uVar9 < 0x10) {
    return;
  }
  if ((0x7f800000 < ((uint)param_1 & 0x7fffffff) ||
      (((uint)param_1 & 0x7fffffff) == 0x7f800000 ||
      (((uint)param_1 & 0x7fffffff) == 0 ||
      (int)param_1 < 0 && ((uint)param_1 & 0x7fffffff) - 1 < 0x7fffff))) ||
      (int)param_1 < 0 && ((uint)param_1 & 0x7fffffff) - 0x800000 >> 0x18 < 0x7f) {
    return;
  }
  __nmemb = (ulong)uVar9 * (ulong)uVar8;
  __ptr = calloc(__nmemb,4);
  if (__ptr == (void *)0x0) {
    return;
  }
  local_80 = 1.0;
  if (param_1 <= 1.0) {
    local_80 = param_1;
  }
  local_90 = param_2;
  pvStack_88 = __ptr;
  b6_rows(uVar9,uVar8,rows,&local_90);
  uVar8 = *param_2;
  uVar7 = (ulong)uVar8;
  uVar9 = param_2[1];
  iVar2 = uVar8 + 0x3e;
  if ((int)(uVar8 + 0x1f) < 0 == SCARRY4(uVar8,0x1f)) {
    iVar2 = uVar8 + 0x1f;
  }
  iVar3 = uVar9 + 0x3e;
  if ((int)(uVar9 + 0x1f) < 0 == SCARRY4(uVar9,0x1f)) {
    iVar3 = uVar9 + 0x1f;
  }
  iVar2 = iVar2 >> 5;
  iVar3 = iVar3 >> 5;
  __ptr_00 = calloc((long)iVar3 * (long)iVar2,1);
  uVar21 = DAT_00100ae0;
  if (__ptr_00 == (void *)0x0) goto LAB_005821d8;
  __ptr_01 = (void *)0x0;
  if ((0 < (int)uVar9) && (0 < (int)uVar8)) {
    uVar19 = uVar7 & 0x7ffffff8;
    auVar31._8_4_ = 0x38d1b717;
    auVar31._0_8_ = 0x38d1b71738d1b717;
    auVar31._12_4_ = 0x38d1b717;
    uVar16 = 0;
    bVar13 = false;
    pauVar20 = (undefined (*) [16])((long)__ptr + 0x10);
    uVar38 = auVar31._8_8_;
    local_d0 = __ptr;
    do {
      uVar12 = (uint)(uVar16 >> 5) & 0x7ffffff;
      iVar4 = 0;
      if (0x1f < uVar16) {
        iVar4 = uVar12 - 1;
      }
      if (iVar4 < iVar3) {
        uVar24 = 0;
        do {
          if (0.0001 < *(float *)((long)__ptr + uVar24 * 4 + uVar16 * uVar7 * 4)) {
            uVar6 = (uint)(uVar24 >> 5) & 0x7ffffff;
            uVar5 = 0;
            if (0x1f < uVar24) {
              uVar5 = uVar6 - 1;
            }
            if ((int)uVar5 < iVar2) {
              uVar10 = (uVar6 + 1) - uVar5;
              uVar6 = iVar2 + ~uVar5;
              if (uVar10 <= iVar2 + ~uVar5) {
                uVar6 = uVar10;
              }
              iVar23 = iVar2 * iVar4 + uVar5;
              iVar22 = iVar4;
              do {
                bVar13 = true;
                memset((void *)((long)__ptr_00 + (long)iVar23),1,(ulong)uVar6 + 1);
                if ((int)uVar12 < iVar22) break;
                iVar22 = iVar22 + 1;
                iVar23 = iVar23 + iVar2;
              } while (iVar22 < iVar3);
            }
            else {
              bVar13 = true;
            }
          }
          uVar24 = uVar24 + 1;
        } while (uVar24 != uVar7);
      }
      else {
        if (uVar8 < 8) {
          uVar24 = 0;
        }
        else {
          auVar37 = ZEXT816(0);
          auVar39 = ZEXT816(0);
          uVar24 = uVar19;
          pauVar17 = pauVar20;
          do {
            pauVar1 = pauVar17 + -1;
            auVar36 = *pauVar17;
            uVar24 = uVar24 - 8;
            pauVar17 = pauVar17 + 2;
            auVar35 = NEON_fcmgt(*pauVar1,auVar31,4);
            auVar36 = NEON_fcmgt(auVar36,auVar31,4);
            bVar25 = auVar37[0] | auVar35[0];
            bVar27 = auVar37[2] | auVar35[4];
            bVar28 = auVar37[4] | auVar35[8];
            bVar29 = auVar37[6] | auVar35[12];
            auVar37 = ZEXT716(CONCAT16(bVar29,(uint6)CONCAT14(bVar28,(uint)CONCAT12(bVar27,(ushort)
                                                  bVar25))));
            bVar30 = auVar39[0] | auVar36[0];
            bVar32 = auVar39[2] | auVar36[4];
            bVar33 = auVar39[4] | auVar36[8];
            bVar34 = auVar39[6] | auVar36[12];
            auVar39 = ZEXT716(CONCAT16(bVar34,(uint6)CONCAT14(bVar33,(uint)CONCAT12(bVar32,(ushort)
                                                  bVar30))));
          } while (uVar24 != 0);
          uVar24 = NEON_cmlt(CONCAT26((ushort)(bVar34 | bVar29) << 0xf,
                                      CONCAT24((ushort)(bVar33 | bVar28) << 0xf,
                                               CONCAT22((ushort)(bVar32 | bVar27) << 0xf,
                                                        (ushort)(bVar30 | bVar25) << 0xf))),0,2);
          uVar26 = NEON_addv(uVar24 & uVar21,2);
          if ((uVar26 & 0xf) != 0) {
            bVar13 = true;
          }
          uVar24 = uVar19;
          if (uVar19 == uVar7) goto LAB_00581f00;
        }
        lVar15 = uVar7 - uVar24;
        pfVar14 = (float *)((long)local_d0 + uVar24 * 4);
        do {
          if (0.0001 < *pfVar14) {
            bVar13 = true;
          }
          lVar15 = lVar15 + -1;
          pfVar14 = pfVar14 + 1;
        } while (lVar15 != 0);
      }
LAB_00581f00:
      auVar31._8_8_ = uVar38;
      auVar31._0_8_ = 0x38d1b71738d1b717;
      uVar16 = uVar16 + 1;
      pauVar20 = (undefined (*) [16])(*pauVar20 + uVar7 * 4);
      local_d0 = (void *)((long)local_d0 + uVar7 * 4);
    } while (uVar16 != uVar9);
    if (bVar13) {
      __ptr_01 = calloc(__nmemb,4);
      if (__ptr_01 != (void *)0x0) {
        local_94 = 0;
        local_b8 = param_2;
        local_b0 = __ptr;
        local_a8 = __ptr_01;
        pvStack_a0 = __ptr_00;
        local_98 = iVar2;
        b6_rows((ulong)uVar9,uVar7,smooth,&local_b8);
        local_94 = 1;
        local_b0 = __ptr_01;
        local_a8 = __ptr;
        b6_rows(param_2[1],*param_2,smooth,&local_b8);
        uVar7 = __nmemb;
        if (__nmemb < 2) {
          uVar7 = 1;
        }
        if (__nmemb < 8) {
          uVar16 = 0;
        }
        else {
          uVar16 = uVar7 & 0x3ffffffffffffff8;
          pauVar20 = (undefined (*) [16])((long)__ptr + 0x10);
          pauVar17 = (undefined (*) [16])(param_3 + 0x10);
          uVar21 = uVar16;
          do {
            pauVar1 = pauVar20 + -1;
            auVar31 = *pauVar20;
            uVar21 = uVar21 - 8;
            pauVar20 = pauVar20 + 2;
            auVar37 = NEON_fcmgt(pauVar17[-1],*pauVar1,4);
            auVar39 = NEON_fcmgt(*pauVar17,auVar31,4);
            auVar37 = NEON_bit(*pauVar1,pauVar17[-1],auVar37,1);
            auVar31 = NEON_bsl(auVar39,*pauVar17,auVar31,1);
            *(long *)(pauVar17[-1] + 8) = auVar37._8_8_;
            *(long *)pauVar17[-1] = auVar37._0_8_;
            *(long *)(*pauVar17 + 8) = auVar31._8_8_;
            *(long *)*pauVar17 = auVar31._0_8_;
            pauVar17 = pauVar17 + 2;
          } while (uVar21 != 0);
          if (__nmemb == uVar16) goto LAB_005821cc;
        }
        lVar15 = uVar7 - uVar16;
        pfVar14 = (float *)(param_3 + uVar16 * 4);
        pfVar18 = (float *)((long)__ptr + uVar16 * 4);
        do {
          fVar11 = *pfVar14;
          if (*pfVar14 <= *pfVar18) {
            fVar11 = *pfVar18;
          }
          lVar15 = lVar15 + -1;
          *pfVar14 = fVar11;
          pfVar14 = pfVar14 + 1;
          pfVar18 = pfVar18 + 1;
        } while (lVar15 != 0);
      }
    }
    else {
      __ptr_01 = (void *)0x0;
    }
  }
LAB_005821cc:
  free(__ptr_01);
  free(__ptr_00);
LAB_005821d8:
  free(__ptr);
  return;
}



/* 00582204 rows */

void rows(uint **param_1,uint param_2,int param_3)

{
  byte *pbVar1;
  byte *pbVar2;
  byte *pbVar3;
  byte *pbVar4;
  uint uVar5;
  uint uVar6;
  uint uVar7;
  int iVar8;
  int iVar9;
  uint uVar10;
  uint uVar11;
  uint uVar12;
  uint uVar13;
  uint uVar14;
  uint uVar15;
  int iVar16;
  int iVar17;
  uint uVar18;
  uint uVar19;
  uint uVar20;
  uint uVar21;
  uint uVar22;
  int iVar23;
  undefined8 uVar24;
  undefined8 uVar25;
  bool bVar26;
  bool bVar27;
  bool bVar28;
  bool bVar29;
  bool bVar30;
  bool bVar31;
  int iVar32;
  int iVar33;
  ulong uVar34;
  uint uVar35;
  uint uVar36;
  uint *puVar37;
  long lVar38;
  long lVar39;
  long lVar40;
  uint uVar41;
  long lVar42;
  int iVar43;
  int iVar44;
  ulong uVar45;
  long lVar46;
  int iVar47;
  long lVar48;
  ulong uVar49;
  ulong uVar50;
  int iVar51;
  ulong uVar52;
  uint uVar53;
  uint uVar54;
  float fVar55;
  float fVar56;
  float fVar57;
  float fVar58;
  float fVar59;
  undefined8 uVar60;
  float fVar61;
  float fVar62;
  float fVar63;
  float fVar64;
  float fVar65;
  float fVar66;
  float fVar67;
  float fVar69;
  undefined8 uVar68;
  float fVar70;
  float fVar71;
  float fVar72;
  float fVar73;
  float fVar74;
  float fVar75;
  undefined8 uVar77;
  float fVar78;
  float fVar79;
  float fVar80;
  float fVar81;
  float fVar82;
  undefined8 uVar83;
  uint local_188;
  uint uStack_184;
  float fVar76;
  
  uVar25 = DAT_00100b30;
  uVar24 = DAT_00100a20;
  puVar37 = *param_1;
  uVar7 = puVar37[1];
  uVar35 = param_2;
  if ((int)param_2 < 0x3b) {
    uVar35 = 0x3a;
  }
  uVar5 = param_3 + 0x34U;
  if ((int)(uVar7 - 6) <= (int)(param_3 + 0x34U)) {
    uVar5 = uVar7 - 6;
  }
  if ((int)(uVar35 - 0x34) < (int)uVar5) {
    uVar6 = *puVar37;
    if (0xc < (int)uVar6) {
      iVar16 = uVar6 * (uVar35 - 0x34);
      uVar52 = (ulong)uVar35 - 0x34;
      uVar77 = NEON_fmov(0x3f800000,4);
      uVar83 = NEON_fmov(0x40400000,4);
      lVar39 = *(long *)(puVar37 + 4);
      uVar35 = iVar16 + 6;
      fVar75 = 1.0;
      fVar76 = 1.0;
      uVar36 = iVar16 * 3 + 0x12;
      do {
        uVar45 = 6;
        local_188 = uVar36;
        uStack_184 = uVar35;
        do {
          lVar38 = uVar52 * uVar6 + uVar45;
          fVar72 = *(float *)(lVar39 + lVar38 * 4);
          if (-3.7 <= fVar72 && fVar72 == -0.1 || -3.7 <= fVar72 && fVar72 < -0.1) {
            lVar46 = *(long *)(puVar37 + 6);
            pbVar1 = (byte *)(lVar46 + lVar38 * 3);
            fVar55 = (float)NEON_ucvtf((uint)pbVar1[1]);
            fVar58 = (float)NEON_ucvtf((uint)pbVar1[2]);
            fVar61 = (float)NEON_ucvtf((uint)*pbVar1);
            fVar56 = fVar55;
            if (fVar55 == fVar58 || fVar58 > fVar55) {
              fVar56 = fVar58;
            }
            fVar69 = fVar55;
            if (fVar58 <= fVar55) {
              fVar69 = fVar58;
            }
            fVar62 = fVar61;
            if (fVar61 <= fVar56) {
              fVar62 = fVar56;
            }
            fVar55 = ((fVar55 - fVar58) + -8.0) / 20.0;
            fVar56 = fVar61;
            if (fVar69 <= fVar61) {
              fVar56 = fVar69;
            }
            fVar58 = ((fVar61 - fVar58) + -5.0) / 20.0;
            fVar79 = (float)uVar25;
            fVar80 = (float)((ulong)uVar25 >> 0x20);
            fVar81 = (float)uVar24;
            fVar61 = (fVar56 + fVar79) / fVar81;
            fVar82 = (float)((ulong)uVar24 >> 0x20);
            fVar69 = ((fVar62 - fVar56) / (fVar62 + 8.0) + fVar80) / fVar82;
            fVar56 = 0.0;
            if (0.0 <= fVar58) {
              fVar56 = fVar58;
            }
            fVar58 = fVar76;
            if (fVar56 <= 1.0) {
              fVar58 = fVar56;
            }
            uVar60 = NEON_fcmlt(CONCAT44(fVar69,fVar61),0,4);
            fVar56 = 0.0;
            if (0.0 <= fVar55) {
              fVar56 = fVar55;
            }
            uVar60 = CONCAT17((byte)((uint)fVar69 >> 0x18) & ~(byte)((ulong)uVar60 >> 0x38),
                              CONCAT16((byte)((uint)fVar69 >> 0x10) & ~(byte)((ulong)uVar60 >> 0x30)
                                       ,CONCAT15((byte)((uint)fVar69 >> 8) &
                                                 ~(byte)((ulong)uVar60 >> 0x28),
                                                 CONCAT14(SUB41(fVar69,0) &
                                                          ~(byte)((ulong)uVar60 >> 0x20),
                                                          CONCAT13((byte)((uint)fVar61 >> 0x18) &
                                                                   ~(byte)((ulong)uVar60 >> 0x18),
                                                                   CONCAT12((byte)((uint)fVar61 >>
                                                                                  0x10) &
                                                                            ~(byte)((ulong)uVar60 >>
                                                                                   0x10),
                                                                            CONCAT11((byte)((uint)
                                                  fVar61 >> 8) & ~(byte)((ulong)uVar60 >> 8),
                                                  SUB41(fVar61,0) & ~(byte)uVar60)))))));
            uVar68 = NEON_fcmgt(uVar60,uVar77,4);
            fVar55 = fVar76;
            if (fVar56 <= 1.0) {
              fVar55 = fVar56;
            }
            uVar60 = NEON_bit(uVar60,uVar77,uVar68,1);
            fVar56 = (float)uVar60;
            fVar61 = (float)((ulong)uVar60 >> 0x20);
            fVar69 = (float)((ulong)uVar83 >> 0x20);
            if ((0.25 <= (1.0 - fVar55 * fVar55 * (3.0 - (fVar55 + fVar55))) *
                         (1.0 - fVar58 * fVar58 * (3.0 - (fVar58 + fVar58))) *
                         (1.0 - fVar61 * fVar61 * (fVar69 - (fVar61 + fVar61))) *
                         fVar56 * fVar56 * ((float)uVar83 - (fVar56 + fVar56))) &&
               ((((0.38 < fVar72 - *(float *)(lVar39 + ((lVar38 << 0x20) + -0x400000000 >> 0x1e)) ||
                  (0.38 < fVar72 - *(float *)(lVar39 + ((lVar38 << 0x20) + 0x400000000 >> 0x1e))))
                 || (0.38 < fVar72 - *(float *)(lVar39 + (long)(int)((int)lVar38 + uVar6 * -4) * 4))
                 ) || (0.38 < fVar72 - *(float *)(lVar39 + (long)(int)(uVar6 * 4 + (int)lVar38) * 4)
                      )))) {
              lVar38 = 0;
              do {
                iVar16 = (&DAT_00571808)[lVar38];
                lVar48 = (long)iVar16;
                iVar8 = (&DAT_00571828)[lVar38];
                iVar44 = (int)uVar45;
                uVar20 = iVar44 + iVar16 * -2;
                iVar51 = (int)uVar52;
                uVar21 = iVar51 + iVar8 * -2;
                uVar22 = iVar51 + iVar8 * -4;
                uVar41 = uVar21 | uVar20;
                bVar30 = uVar41 != 0xffffffff;
                uVar53 = iVar44 + iVar16 * -4;
                bVar28 = (int)(uVar41 + 1) < 0 == SCARRY4(uVar41,1);
                bVar26 = false;
                if (bVar30 && bVar28) {
                  bVar26 = (int)(uVar6 - uVar20) < 0;
                }
                bVar31 = uVar6 != uVar20;
                lVar40 = (long)(int)(uVar20 + uVar21 * uVar6);
                bVar26 = bVar26 == ((bVar30 && bVar28) && SBORROW4(uVar6,uVar20));
                bVar27 = false;
                if (((bVar30 && bVar28) && bVar31) && bVar26) {
                  bVar27 = (int)(uVar7 - uVar21) < 0;
                }
                uVar41 = uVar22 | uVar53;
                if (((((!bVar30 || !bVar28) || !bVar31) || !bVar26) || uVar7 == uVar21) ||
                    bVar27 != ((((bVar30 && bVar28) && bVar31) && bVar26) && SBORROW4(uVar7,uVar21))
                   ) {
                  lVar40 = -1;
                }
                bVar30 = uVar41 != 0xffffffff;
                bVar28 = (int)(uVar41 + 1) < 0 == SCARRY4(uVar41,1);
                bVar26 = false;
                if (bVar30 && bVar28) {
                  bVar26 = (int)(uVar6 - uVar53) < 0;
                }
                bVar31 = uVar6 != uVar53;
                lVar42 = (long)(int)(uVar53 + uVar22 * uVar6);
                bVar26 = bVar26 == ((bVar30 && bVar28) && SBORROW4(uVar6,uVar53));
                bVar27 = false;
                if (((bVar30 && bVar28) && bVar31) && bVar26) {
                  bVar27 = (int)(uVar7 - uVar22) < 0;
                }
                if (((((!bVar30 || !bVar28) || !bVar31) || !bVar26) || uVar7 == uVar22) ||
                    bVar27 != ((((bVar30 && bVar28) && bVar31) && bVar26) && SBORROW4(uVar7,uVar22))
                   ) {
                  lVar42 = -1;
                }
                fVar56 = *(float *)(lVar39 + lVar40 * 4);
                fVar55 = *(float *)(lVar39 + lVar42 * 4);
                if (fVar55 <= fVar56) {
                  fVar56 = fVar55;
                }
                if (0.4 <= fVar72 - fVar56) {
                  fVar56 = 0.0;
                  uVar41 = iVar51 + iVar16 * -9;
                  iVar9 = iVar8 * -3 + uVar6 * 3 * iVar16;
                  iVar17 = -iVar8;
                  iVar43 = iVar44 + uVar6 * uVar41;
                  iVar23 = iVar8 * 9;
                  iVar47 = iVar44 + uVar6 * (uVar22 + iVar16 * -9) + iVar16 * -4;
                  iVar32 = iVar44 + iVar16 * -4;
                  iVar33 = 7;
                  uVar34 = uVar45;
                  do {
                    if (iVar33 != 4) {
                      uVar20 = iVar23 + (int)uVar34;
                      uVar22 = uVar41 | uVar20;
                      bVar30 = uVar22 != 0xffffffff;
                      uVar21 = iVar23 + iVar43;
                      bVar28 = (int)(uVar22 + 1) < 0 == SCARRY4(uVar22,1);
                      bVar26 = false;
                      if (bVar30 && bVar28) {
                        bVar26 = (int)(uVar6 - uVar20) < 0;
                      }
                      bVar31 = uVar6 != uVar20;
                      uVar22 = iVar8 * -4 + uVar41;
                      bVar26 = bVar26 == ((bVar30 && bVar28) && SBORROW4(uVar6,uVar20));
                      bVar27 = false;
                      if (((bVar30 && bVar28) && bVar31) && bVar26) {
                        bVar27 = (int)(uVar7 - uVar41) < 0;
                      }
                      if (((((!bVar30 || !bVar28) || !bVar31) || !bVar26) || uVar7 == uVar41) ||
                          bVar27 != ((((bVar30 && bVar28) && bVar31) && bVar26) &&
                                    SBORROW4(uVar7,uVar41))) {
                        uVar21 = 0xffffffff;
                      }
                      if ((((int)uVar22 < (int)uVar7) && (iVar23 + iVar32 < (int)uVar6)) &&
                         ((-1 < (int)(uVar22 | iVar23 + iVar32) &&
                          ((-1 < (int)uVar21 && (-1 < iVar23 + iVar47)))))) {
                        fVar58 = *(float *)(lVar39 + (ulong)uVar21 * 4);
                        fVar61 = fVar58 - fVar72;
                        fVar55 = -fVar61;
                        if (0.0 <= fVar61) {
                          fVar55 = fVar61;
                        }
                        if (fVar55 < 0.2) {
                          fVar61 = (float)NEON_ucvtf((uint)pbVar1[1]);
                          fVar62 = (float)NEON_ucvtf((uint)pbVar1[2]);
                          fVar64 = (float)NEON_ucvtf((uint)*pbVar1);
                          pbVar2 = (byte *)(lVar46 + (ulong)uVar21 * 3);
                          fVar71 = (float)NEON_ucvtf((uint)pbVar2[1]);
                          fVar73 = (float)NEON_ucvtf((uint)pbVar2[2]);
                          fVar74 = (float)NEON_ucvtf((uint)*pbVar2);
                          fVar55 = fVar61;
                          if (fVar61 <= fVar62) {
                            fVar55 = fVar62;
                          }
                          fVar70 = fVar64;
                          if (fVar64 <= fVar55) {
                            fVar70 = fVar55;
                          }
                          fVar55 = fVar71;
                          if (fVar71 <= fVar73) {
                            fVar55 = fVar73;
                          }
                          fVar70 = fVar70 + 8.0;
                          fVar78 = fVar74;
                          if (fVar74 <= fVar55) {
                            fVar78 = fVar55;
                          }
                          fVar78 = fVar78 + 8.0;
                          fVar64 = fVar64 / fVar70 - fVar74 / fVar78;
                          fVar61 = fVar61 / fVar70 - fVar71 / fVar78;
                          fVar55 = -fVar64;
                          if (0.0 <= fVar64) {
                            fVar55 = fVar64;
                          }
                          fVar64 = -fVar61;
                          if (0.0 <= fVar61) {
                            fVar64 = fVar61;
                          }
                          fVar62 = fVar62 / fVar70 - fVar73 / fVar78;
                          fVar61 = -fVar62;
                          if (0.0 <= fVar62) {
                            fVar61 = fVar62;
                          }
                          if (fVar61 + fVar55 + fVar64 < 0.1) {
                            fVar58 = ((fVar58 - *(float *)(lVar39 + (ulong)(uint)(iVar23 + iVar47) *
                                                                    4)) + -0.28) / 0.37;
                            fVar55 = 0.0;
                            if (0.0 <= fVar58) {
                              fVar55 = fVar58;
                            }
                            fVar58 = fVar76;
                            if (fVar55 <= 1.0) {
                              fVar58 = fVar55;
                            }
                            fVar56 = fVar56 + fVar58 * fVar58 * (3.0 - (fVar58 + fVar58)) *
                                              0.1666667;
                          }
                        }
                      }
                    }
                    iVar33 = iVar33 + -1;
                    iVar47 = iVar47 + iVar9;
                    uVar41 = uVar41 + iVar16 * 3;
                    iVar43 = iVar43 + iVar9;
                    iVar32 = iVar32 + iVar8 * -3;
                    uVar34 = (ulong)(uint)((int)uVar34 + iVar8 * -3);
                  } while (iVar33 != 0);
                  if (0.6 <= fVar56) {
                    uVar41 = iVar8 * 2 + iVar51;
                    uVar20 = iVar16 * 2 + iVar44;
                    lVar40 = 0;
                    uVar21 = iVar16 * 5 + iVar44;
                    uVar22 = iVar8 * 5 + iVar51;
                    bVar28 = false;
                    if ((int)uVar21 < (int)uVar6) {
                      bVar28 = (int)(uVar7 - uVar22) < 0;
                    }
                    iVar47 = iVar16 + uVar6 * iVar8;
                    do {
                      iVar43 = (&DAT_00571860)[lVar40 * 3];
                      iVar9 = (&DAT_00571868)[lVar40 * 3];
                      uVar54 = iVar44 + iVar43 * iVar16;
                      uVar10 = iVar51 + iVar43 * iVar8;
                      uVar11 = iVar44 + (&DAT_00571864)[lVar40 * 3] * iVar16;
                      uVar12 = iVar51 + (&DAT_00571864)[lVar40 * 3] * iVar8;
                      uVar18 = uVar10 | uVar54;
                      uVar53 = uVar54 + uVar10 * uVar6;
                      bVar31 = uVar18 != 0xffffffff;
                      uVar13 = iVar44 + iVar9 * iVar16;
                      bVar26 = (int)(uVar18 + 1) < 0 == SCARRY4(uVar18,1);
                      bVar30 = false;
                      if (bVar31 && bVar26) {
                        bVar30 = (int)(uVar6 - uVar54) < 0;
                      }
                      bVar27 = uVar6 != uVar54;
                      uVar19 = uVar12 | uVar11;
                      uVar18 = iVar51 + iVar9 * iVar8;
                      bVar30 = bVar30 == ((bVar31 && bVar26) && SBORROW4(uVar6,uVar54));
                      bVar29 = false;
                      if (((bVar31 && bVar26) && bVar27) && bVar30) {
                        bVar29 = (int)(uVar7 - uVar10) < 0;
                      }
                      if (((((!bVar31 || !bVar26) || !bVar27) || !bVar30) || uVar7 == uVar10) ||
                          bVar29 != ((((bVar31 && bVar26) && bVar27) && bVar30) &&
                                    SBORROW4(uVar7,uVar10))) {
                        uVar53 = 0xffffffff;
                      }
                      bVar31 = uVar19 != 0xffffffff;
                      uVar14 = uVar11 + uVar12 * uVar6;
                      bVar26 = (int)(uVar19 + 1) < 0 == SCARRY4(uVar19,1);
                      bVar30 = false;
                      if (bVar31 && bVar26) {
                        bVar30 = (int)(uVar6 - uVar11) < 0;
                      }
                      bVar27 = uVar6 != uVar11;
                      uVar19 = uVar18 | uVar13;
                      bVar30 = bVar30 == ((bVar31 && bVar26) && SBORROW4(uVar6,uVar11));
                      bVar29 = false;
                      if (((bVar31 && bVar26) && bVar27) && bVar30) {
                        bVar29 = (int)(uVar7 - uVar12) < 0;
                      }
                      if (((((!bVar31 || !bVar26) || !bVar27) || !bVar30) || uVar7 == uVar12) ||
                          bVar29 != ((((bVar31 && bVar26) && bVar27) && bVar30) &&
                                    SBORROW4(uVar7,uVar12))) {
                        uVar14 = 0xffffffff;
                      }
                      bVar31 = uVar19 != 0xffffffff;
                      uVar15 = uVar13 + uVar18 * uVar6;
                      bVar26 = (int)(uVar19 + 1) < 0 == SCARRY4(uVar19,1);
                      bVar30 = false;
                      if (bVar31 && bVar26) {
                        bVar30 = (int)(uVar6 - uVar13) < 0;
                      }
                      bVar27 = uVar6 != uVar13;
                      bVar30 = bVar30 == ((bVar31 && bVar26) && SBORROW4(uVar6,uVar13));
                      bVar29 = false;
                      if (((bVar31 && bVar26) && bVar27) && bVar30) {
                        bVar29 = (int)(uVar7 - uVar18) < 0;
                      }
                      if (((((!bVar31 || !bVar26) || !bVar27) || !bVar30) || uVar7 == uVar18) ||
                          bVar29 != ((((bVar31 && bVar26) && bVar27) && bVar30) &&
                                    SBORROW4(uVar7,uVar18))) {
                        uVar15 = 0xffffffff;
                      }
                      if (((-1 < (int)uVar53) && (-1 < (int)uVar14)) && (-1 < (int)uVar15)) {
                        pbVar2 = (byte *)(lVar46 + (ulong)uVar14 + (ulong)uVar14 * 2);
                        fVar58 = (float)NEON_ucvtf((uint)pbVar2[1]);
                        fVar61 = (float)NEON_ucvtf((uint)pbVar2[2]);
                        fVar62 = (float)NEON_ucvtf((uint)*pbVar2);
                        fVar55 = fVar58;
                        if (fVar58 == fVar61 || fVar61 > fVar58) {
                          fVar55 = fVar61;
                        }
                        fVar64 = fVar58;
                        if (fVar61 <= fVar58) {
                          fVar64 = fVar61;
                        }
                        fVar71 = fVar62;
                        if (fVar62 <= fVar55) {
                          fVar71 = fVar55;
                        }
                        fVar58 = ((fVar58 - fVar61) + -8.0) / 20.0;
                        fVar55 = fVar62;
                        if (fVar64 <= fVar62) {
                          fVar55 = fVar64;
                        }
                        fVar61 = ((fVar62 - fVar61) + -5.0) / 20.0;
                        fVar62 = (fVar55 + fVar79) / fVar81;
                        fVar64 = ((fVar71 - fVar55) / (fVar71 + 8.0) + fVar80) / fVar82;
                        fVar55 = 0.0;
                        if (0.0 <= fVar61) {
                          fVar55 = fVar61;
                        }
                        fVar61 = fVar76;
                        if (fVar55 <= 1.0) {
                          fVar61 = fVar55;
                        }
                        uVar60 = NEON_fcmlt(CONCAT44(fVar64,fVar62),0,4);
                        fVar55 = 0.0;
                        if (0.0 <= fVar58) {
                          fVar55 = fVar58;
                        }
                        uVar60 = CONCAT17((byte)((uint)fVar64 >> 0x18) &
                                          ~(byte)((ulong)uVar60 >> 0x38),
                                          CONCAT16((byte)((uint)fVar64 >> 0x10) &
                                                   ~(byte)((ulong)uVar60 >> 0x30),
                                                   CONCAT15((byte)((uint)fVar64 >> 8) &
                                                            ~(byte)((ulong)uVar60 >> 0x28),
                                                            CONCAT14(SUB41(fVar64,0) &
                                                                     ~(byte)((ulong)uVar60 >> 0x20),
                                                                     CONCAT13((byte)((uint)fVar62 >>
                                                                                    0x18) &
                                                                              ~(byte)((ulong)uVar60
                                                                                     >> 0x18),
                                                                              CONCAT12((byte)((uint)
                                                  fVar62 >> 0x10) & ~(byte)((ulong)uVar60 >> 0x10),
                                                  CONCAT11((byte)((uint)fVar62 >> 8) &
                                                           ~(byte)((ulong)uVar60 >> 8),
                                                           SUB41(fVar62,0) & ~(byte)uVar60)))))));
                        uVar68 = NEON_fcmgt(uVar60,uVar77,4);
                        fVar58 = fVar76;
                        if (fVar55 <= 1.0) {
                          fVar58 = fVar55;
                        }
                        uVar60 = NEON_bit(uVar60,uVar77,uVar68,1);
                        fVar55 = (float)uVar60;
                        fVar62 = (float)((ulong)uVar60 >> 0x20);
                        fVar55 = (1.0 - fVar58 * fVar58 * (3.0 - (fVar58 + fVar58))) *
                                 (1.0 - fVar61 * fVar61 * (3.0 - (fVar61 + fVar61))) *
                                 (1.0 - fVar62 * fVar62 * (fVar69 - (fVar62 + fVar62))) *
                                 fVar55 * fVar55 * ((float)uVar83 - (fVar55 + fVar55));
                        if (0.4 <= fVar55) {
                          pbVar3 = (byte *)(lVar46 + (ulong)uVar53 + (ulong)uVar53 * 2);
                          pbVar4 = (byte *)(lVar46 + (ulong)uVar15 + (ulong)uVar15 * 2);
                          fVar61 = (float)NEON_ucvtf((uint)pbVar3[1]);
                          fVar62 = (float)NEON_ucvtf((uint)pbVar3[2]);
                          fVar64 = (float)NEON_ucvtf((uint)*pbVar3);
                          fVar71 = (float)NEON_ucvtf((uint)pbVar4[1]);
                          fVar73 = (float)NEON_ucvtf((uint)pbVar4[2]);
                          fVar74 = (float)NEON_ucvtf((uint)*pbVar4);
                          fVar58 = fVar61;
                          if (fVar61 <= fVar62) {
                            fVar58 = fVar62;
                          }
                          fVar70 = fVar64;
                          if (fVar64 <= fVar58) {
                            fVar70 = fVar58;
                          }
                          fVar58 = fVar71;
                          if (fVar71 <= fVar73) {
                            fVar58 = fVar73;
                          }
                          fVar70 = fVar70 + 8.0;
                          fVar78 = fVar74;
                          if (fVar74 <= fVar58) {
                            fVar78 = fVar58;
                          }
                          fVar78 = fVar78 + 8.0;
                          fVar64 = fVar64 / fVar70 - fVar74 / fVar78;
                          fVar61 = fVar61 / fVar70 - fVar71 / fVar78;
                          fVar58 = -fVar64;
                          if (0.0 <= fVar64) {
                            fVar58 = fVar64;
                          }
                          fVar64 = -fVar61;
                          if (0.0 <= fVar61) {
                            fVar64 = fVar61;
                          }
                          fVar62 = fVar62 / fVar70 - fVar73 / fVar78;
                          fVar61 = -fVar62;
                          if (0.0 <= fVar62) {
                            fVar61 = fVar62;
                          }
                          if (fVar61 + fVar58 + fVar64 <= 0.12) {
                            fVar61 = (float)tanmean(puVar37,uVar54,uVar10,iVar17);
                            fVar64 = (float)tanmean(puVar37,uVar11,uVar12,iVar17,lVar48);
                            fVar62 = (float)tanmean(puVar37,uVar13,uVar18,iVar17,lVar48);
                            fVar58 = fVar64;
                            if (fVar64 == fVar62 || fVar62 > fVar64) {
                              fVar58 = fVar62;
                            }
                            fVar71 = fVar64;
                            if (fVar62 <= fVar64) {
                              fVar71 = fVar62;
                            }
                            fVar73 = fVar61;
                            if (fVar61 <= fVar58) {
                              fVar73 = fVar58;
                            }
                            fVar58 = fVar61;
                            if (fVar71 <= fVar61) {
                              fVar58 = fVar71;
                            }
                            if (fVar73 - fVar58 <= 0.22) {
                              fVar70 = (fVar62 - fVar61) / (float)(iVar9 - iVar43);
                              fVar74 = fVar70 * (float)iVar43;
                              fVar71 = -0.24;
                              if (-0.24 <= fVar74) {
                                fVar71 = fVar74;
                              }
                              fVar74 = 0.24;
                              if (fVar71 <= 0.24) {
                                fVar74 = fVar71;
                              }
                              fVar71 = fVar73;
                              if (fVar73 <= fVar61 - fVar74) {
                                fVar71 = fVar61 - fVar74;
                              }
                              if (((((((int)uVar21 < (int)uVar6 && uVar7 != uVar22) &&
                                     bVar28 == ((int)uVar21 < (int)uVar6 && SBORROW4(uVar7,uVar22)))
                                    && -1 < (int)(uVar22 | uVar21)) && -1 < (int)(uVar41 | uVar20))
                                  && -1 < (int)(uVar20 + uVar41 * uVar6)) &&
                                  -1 < (int)(uVar21 + uVar22 * uVar6)) {
                                fVar64 = fVar64 + (fVar61 + fVar62) * -0.5;
                                fVar62 = -fVar64;
                                if (0.0 <= fVar64) {
                                  fVar62 = fVar64;
                                }
                                fVar64 = (float)tanmean(puVar37,uVar20,uVar41,iVar17);
                                fVar74 = (float)tanmean(puVar37,uVar21,uVar22,iVar17,lVar48);
                                fVar62 = (fVar62 + -0.035) / 0.055;
                                fVar78 = ((fVar73 - fVar58) + -0.1) / 0.12;
                                fVar58 = 0.0;
                                if (0.0 <= fVar62) {
                                  fVar58 = fVar62;
                                }
                                fVar65 = ((fVar74 - fVar71) + -0.018) / 0.047;
                                fVar62 = fVar75;
                                if (fVar58 <= 1.0) {
                                  fVar62 = fVar58;
                                }
                                fVar58 = 0.0;
                                if (0.0 <= fVar78) {
                                  fVar58 = fVar78;
                                }
                                fVar74 = (((fVar74 - fVar71) - (fVar64 - fVar71)) + -0.03) / 0.06;
                                fVar64 = fVar76;
                                if (fVar58 <= 1.0) {
                                  fVar64 = fVar58;
                                }
                                fVar58 = 0.0;
                                if (0.0 <= fVar65) {
                                  fVar58 = fVar65;
                                }
                                fVar78 = fVar75;
                                if (fVar58 <= 1.0) {
                                  fVar78 = fVar58;
                                }
                                fVar58 = 0.0;
                                if (0.0 <= fVar74) {
                                  fVar58 = fVar74;
                                }
                                fVar74 = fVar76;
                                if (fVar58 <= 1.0) {
                                  fVar74 = fVar58;
                                }
                                fVar55 = (1.0 - fVar74 * fVar74 * (3.0 - (fVar74 + fVar74))) *
                                         ((float)DAT_00100b38 -
                                         fVar64 * fVar64 * (3.0 - (fVar64 + fVar64))) *
                                         (1.0 - fVar62 * fVar62 * (3.0 - (fVar62 + fVar62))) *
                                         fVar55 * fVar56 * *(float *)(param_1 + 2) *
                                         ((float)((ulong)DAT_00100b38 >> 0x20) - fVar78 * 2.0) *
                                         fVar78 * fVar78;
                                if (0.15 <= fVar55) {
                                  uVar10 = (&DAT_00571884)[lVar40];
                                  uVar34 = 0;
                                  fVar58 = (float)uVar10 * 0.7;
                                  uVar49 = uVar45;
                                  uVar50 = uVar52;
                                  uVar53 = local_188;
                                  uVar54 = uStack_184;
                                  do {
                                    if ((((long)(int)uVar7 <= (long)uVar50) ||
                                        ((long)(ulong)uVar6 <= (long)uVar49)) ||
                                       (((int)((uint)uVar50 | (uint)uVar49) < 0 || ((int)uVar54 < 0)
                                        ))) break;
                                    if ((((long)(int)param_2 <= (long)uVar50) &&
                                        ((long)uVar50 < (long)param_3)) &&
                                       (fVar71 + -0.035 <= *(float *)(lVar39 + (ulong)uVar54 * 4)))
                                    {
                                      fVar74 = (float)NEON_ucvtf((uint)pbVar2[1]);
                                      fVar78 = (float)NEON_ucvtf((uint)pbVar2[2]);
                                      fVar64 = fVar70 * (float)iVar43;
                                      fVar65 = (float)NEON_ucvtf((uint)*pbVar2);
                                      fVar62 = -0.24;
                                      if (-0.24 <= fVar64) {
                                        fVar62 = fVar64;
                                      }
                                      pbVar3 = (byte *)(lVar46 + (ulong)uVar53);
                                      fVar63 = (float)NEON_ucvtf((uint)pbVar3[2]);
                                      fVar64 = 0.24;
                                      if (fVar62 <= 0.24) {
                                        fVar64 = fVar62;
                                      }
                                      fVar59 = (float)NEON_ucvtf((uint)pbVar3[1]);
                                      fVar62 = fVar73;
                                      if (fVar73 <= fVar61 - fVar64) {
                                        fVar62 = fVar61 - fVar64;
                                      }
                                      fVar57 = (float)NEON_ucvtf((uint)*pbVar3);
                                      fVar64 = fVar59;
                                      if (fVar59 <= fVar63) {
                                        fVar64 = fVar63;
                                      }
                                      fVar66 = fVar57;
                                      if (fVar57 <= fVar64) {
                                        fVar66 = fVar64;
                                      }
                                      fVar64 = fVar74;
                                      if (fVar74 <= fVar78) {
                                        fVar64 = fVar78;
                                      }
                                      fVar66 = fVar66 + 8.0;
                                      fVar67 = fVar65;
                                      if (fVar65 <= fVar64) {
                                        fVar67 = fVar64;
                                      }
                                      fVar67 = fVar67 + 8.0;
                                      fVar65 = fVar57 / fVar66 - fVar65 / fVar67;
                                      fVar74 = fVar59 / fVar66 - fVar74 / fVar67;
                                      fVar64 = -fVar65;
                                      if (0.0 <= fVar65) {
                                        fVar64 = fVar65;
                                      }
                                      fVar65 = -fVar74;
                                      if (0.0 <= fVar74) {
                                        fVar65 = fVar74;
                                      }
                                      fVar78 = fVar63 / fVar66 - fVar78 / fVar67;
                                      fVar74 = -fVar78;
                                      if (0.0 <= fVar78) {
                                        fVar74 = fVar78;
                                      }
                                      fVar74 = (fVar74 + fVar64 + fVar65 + -0.08) / 0.14;
                                      fVar64 = 0.0;
                                      if (0.0 <= fVar74) {
                                        fVar64 = fVar74;
                                      }
                                      fVar74 = fVar76;
                                      if (fVar64 <= 1.0) {
                                        fVar74 = fVar64;
                                      }
                                      fVar64 = (float)tanmean(puVar37,uVar49 & 0xffffffff,
                                                              uVar50 & 0xffffffff,iVar17);
                                      fVar64 = (fVar64 - fVar62) + -0.012;
                                      fVar78 = ((float)(uVar34 & 0xffffffff) - fVar58) /
                                               (((float)uVar10 + 1.0) - fVar58);
                                      fVar62 = 0.0;
                                      if (0.0 <= fVar64) {
                                        fVar62 = fVar64;
                                      }
                                      fVar64 = 0.38;
                                      if (fVar62 <= 0.38) {
                                        fVar64 = fVar62;
                                      }
                                      fVar62 = 0.0;
                                      if (0.0 <= fVar78) {
                                        fVar62 = fVar78;
                                      }
                                      fVar78 = fVar75;
                                      if (fVar62 <= 1.0) {
                                        fVar78 = fVar62;
                                      }
                                      fVar64 = (1.0 - fVar78 * fVar78 * (3.0 - (fVar78 + fVar78))) *
                                               fVar55 * fVar64 *
                                               (1.0 - fVar74 * fVar74 * (3.0 - (fVar74 + fVar74)));
                                      fVar62 = 0.5;
                                      if (uVar34 != 0) {
                                        fVar62 = 0.8;
                                      }
                                      fVar62 = fVar62 * fVar64;
                                      if (1 < uVar34) {
                                        fVar62 = fVar64;
                                      }
                                      fVar64 = (float)NEON_fminnm(fVar62,0x3eae147b);
                                      fVar62 = (float)param_1[1][uVar54];
                                      if (fVar62 <= fVar64) {
                                        fVar62 = fVar64;
                                      }
                                      param_1[1][uVar54] = (uint)fVar62;
                                    }
                                    uVar34 = uVar34 + 1;
                                    iVar43 = iVar43 + -1;
                                    uVar50 = uVar50 + (long)iVar8;
                                    uVar49 = uVar49 + lVar48;
                                    uVar53 = uVar53 + iVar47 * 3;
                                    uVar54 = uVar54 + iVar47;
                                  } while ((uVar10 & ((int)uVar10 >> 0x1f ^ 0xffffffffU)) + 1 !=
                                           uVar34);
                                }
                              }
                            }
                          }
                        }
                      }
                      lVar40 = lVar40 + 1;
                    } while (lVar40 != 3);
                  }
                }
                lVar38 = lVar38 + 1;
              } while (lVar38 != 8);
            }
          }
          uVar45 = uVar45 + 1;
          local_188 = local_188 + 3;
          uStack_184 = uStack_184 + 1;
        } while (uVar45 != uVar6 - 6);
        uVar52 = uVar52 + 1;
        uVar36 = uVar36 + uVar6 * 3;
        uVar35 = uVar35 + uVar6;
      } while (uVar52 != uVar5);
    }
  }
  return;
}


