/* Image base: 00100000 */

/* 00586878 triple */

ulong triple(undefined4 param_1,long *param_2,undefined8 param_3,undefined8 param_4,
            undefined8 param_5)

{
  char cVar1;
  ulong uVar2;
  undefined4 local_48 [2];
  undefined4 local_40;
  undefined4 local_38;
  
  uVar2 = (**(code **)(*param_2 + 0x108))(param_2,param_4,param_5,"(FFF)V");
  if (uVar2 != 0) {
    cVar1 = (**(code **)(*param_2 + 0x720))(param_2);
    if (cVar1 == '\0') {
      local_48[0] = param_1;
      local_40 = param_1;
      local_38 = param_1;
      (**(code **)(*param_2 + 0x1f8))(param_2,param_3,uVar2,local_48);
      cVar1 = (**(code **)(*param_2 + 0x720))(param_2);
      return (ulong)(cVar1 == '\0');
    }
    uVar2 = 0;
  }
  return uVar2;
}



/* 00586950 scalar */

ulong scalar(undefined4 param_1,long *param_2,undefined8 param_3,undefined8 param_4,
            undefined8 param_5)

{
  char cVar1;
  ulong uVar2;
  undefined4 local_38 [2];
  
  uVar2 = (**(code **)(*param_2 + 0x108))(param_2,param_4,param_5,&DAT_00575d0b);
  if (uVar2 != 0) {
    cVar1 = (**(code **)(*param_2 + 0x720))(param_2);
    if (cVar1 == '\0') {
      local_38[0] = param_1;
      (**(code **)(*param_2 + 0x1f8))(param_2,param_3,uVar2,local_38);
      cVar1 = (**(code **)(*param_2 + 0x720))(param_2);
      return (ulong)(cVar1 == '\0');
    }
    uVar2 = 0;
  }
  return uVar2;
}



/* 00586a20 Java_com_codex_lmoments_LegendaryPostProcessor_applyStyle */

int Java_com_codex_lmoments_LegendaryPostProcessor_applyStyle
              (long *param_1,undefined8 param_2,undefined8 param_3,undefined8 param_4,
              undefined8 param_5,undefined8 param_6,undefined4 param_7,int param_8,int param_9)

{
  undefined8 uVar1;
  undefined8 uVar2;
  undefined8 uVar3;
  char cVar4;
  void *__pointer;
  long lVar5;
  code *pcVar6;
  undefined8 uVar7;
  long lVar8;
  int iVar9;
  float fVar10;
  long local_88;
  
  cVar4 = (**(code **)(*param_1 + 0x720))();
  if (cVar4 != '\0') {
    return 0;
  }
  pthread_once((pthread_once_t *)&once,init_key);
  if (key_ok == 0) {
LAB_00586b50:
    __pointer = (void *)0x0;
  }
  else {
    __pointer = pthread_getspecific(key);
    if (__pointer == (void *)0x0) {
      __pointer = calloc(1,0x18);
      if (__pointer == (void *)0x0) goto LAB_00586b54;
      iVar9 = (**(code **)(*param_1 + 0x6d8))(param_1,__pointer);
      if ((iVar9 != 0) || (iVar9 = pthread_setspecific(key,__pointer), iVar9 != 0)) {
        free(__pointer);
        goto LAB_00586b50;
      }
    }
    if (*(long *)((long)__pointer + 8) != 0) {
      (**(code **)(*param_1 + 0x718))(param_1);
      *(undefined8 *)((long)__pointer + 8) = 0;
    }
    b8_color_free(*(undefined8 *)((long)__pointer + 0x10));
    *(undefined8 *)((long)__pointer + 0x10) = 0;
  }
LAB_00586b54:
  lVar5 = dlopen("libzxbase.so",2);
  if (lVar5 == 0) {
    __android_log_print(6,"LeicaM9M3B12","Required original library unavailable");
    return 0;
  }
  pcVar6 = (code *)dlsym(lVar5,"Java_com_codex_lmoments_LegendaryPostProcessor_applyStyle");
  if (pcVar6 == (code *)0x0) {
    __android_log_print(6,"LeicaM9M3B12","Missing original entry: %s",
                        "Java_com_codex_lmoments_LegendaryPostProcessor_applyStyle");
    dlclose(lVar5);
    return 0;
  }
  uVar1 = b6_now_ms();
  fVar10 = (float)param_9;
  local_88 = 0;
  uVar7 = snapshot((float)param_8,fVar10,param_1,param_3,0,&local_88);
  uVar2 = b6_now_ms();
  cVar4 = (**(code **)(*param_1 + 0x720))(param_1);
  if (cVar4 == '\0') {
    iVar9 = (int)fVar10;
    if (19000 < param_9 - 1000U) {
      iVar9 = 0x157c;
    }
    cVar4 = (*pcVar6)(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,iVar9);
    uVar3 = b6_now_ms();
    if ((cVar4 != '\0') && (cVar4 = (**(code **)(*param_1 + 0x720))(param_1), cVar4 == '\0')) {
      iVar9 = finish(fVar10,uVar1,uVar2,uVar3,param_1,param_3,uVar7,local_88,0,1,1);
      if ((__pointer != (void *)0x0) && ((iVar9 != 0 && (local_88 != 0)))) {
        lVar8 = (**(code **)(*param_1 + 0x710))(param_1,param_3);
        *(long *)((long)__pointer + 8) = lVar8;
        if ((lVar8 == 0) ||
           (cVar4 = (**(code **)(*param_1 + 0x720))(param_1), lVar8 = local_88, cVar4 != '\0')) {
          cVar4 = (**(code **)(*param_1 + 0x720))(param_1);
          if (cVar4 != '\0') {
            (**(code **)(*param_1 + 0x88))(param_1);
          }
          if (*(long *)((long)__pointer + 8) != 0) {
            (**(code **)(*param_1 + 0x718))(param_1);
            *(undefined8 *)((long)__pointer + 8) = 0;
          }
          b8_color_free(*(undefined8 *)((long)__pointer + 0x10));
          *(undefined8 *)((long)__pointer + 0x10) = 0;
          __android_log_print(5,"LeicaM9M3B12",
                              "B12 cross_stage_reference_unavailable; next stage takes fresh input reference"
                             );
        }
        else {
          local_88 = 0;
          *(long *)((long)__pointer + 0x10) = lVar8;
        }
        iVar9 = 1;
      }
      goto LAB_00586cc0;
    }
    b4_free(uVar7);
    __android_log_print(6,"LeicaM9M3B12",
                        "B12 upstream_failed stage=1 recovery=fresh_source_requested");
  }
  else {
    b4_free(uVar7);
  }
  iVar9 = 0;
LAB_00586cc0:
  b8_color_free(local_88);
  dlclose(lVar5);
  return iVar9;
}



/* 00586dd8 snapshot */

undefined8
snapshot(undefined4 param_1,undefined4 param_2,long *param_3,undefined8 param_4,undefined4 param_5,
        undefined8 *param_6)

{
  char cVar1;
  int iVar2;
  undefined8 uVar3;
  undefined8 uVar4;
  undefined8 local_60;
  undefined8 local_58;
  undefined8 local_50;
  undefined4 local_48;
  
  local_58 = 0;
  local_50 = 0;
  local_48 = 0;
  local_60 = 0;
  if (param_6 != (undefined8 *)0x0) {
    *param_6 = 0;
  }
  cVar1 = (**(code **)(*param_3 + 0x720))(param_3);
  if (((cVar1 != '\0') || (iVar2 = AndroidBitmap_getInfo(param_3,param_4,&local_58), iVar2 != 0)) ||
     (local_50._4_4_ != 1)) {
    return 0;
  }
  if ((uint)local_58 != 0) {
    if (0x8000 < (uint)local_58) {
      return 0;
    }
    if (local_58._4_4_ - 0x8001U < 0xffff8000) {
      return 0;
    }
    if ((int)(uint)local_50 < 0) {
      return 0;
    }
    if ((uint)local_50 < (uint)local_58 << 2) {
      return 0;
    }
    if (80000000 < local_58._4_4_ * (uint)local_58) {
      return 0;
    }
    iVar2 = AndroidBitmap_lockPixels(param_3,param_4,&local_60);
    if (iVar2 == 0) {
      uVar3 = b6_reference_snapshot
                        (local_60,local_58 & 0xffffffff,local_58._4_4_,local_50 & 0xffffffff,param_5
                        );
      if (param_6 != (undefined8 *)0x0) {
        uVar4 = b8_color_reference(param_1,param_2,local_60,local_58 & 0xffffffff,local_58._4_4_,
                                   local_50 & 0xffffffff);
        *param_6 = uVar4;
      }
      iVar2 = AndroidBitmap_unlockPixels(param_3,param_4);
      if (iVar2 == 0) {
        return uVar3;
      }
      b4_free(uVar3);
      if (param_6 != (undefined8 *)0x0) {
        b8_color_free(*param_6);
        *param_6 = 0;
        return 0;
      }
    }
  }
  return 0;
}



/* 00586f94 finish */

bool finish(float param_1,double param_2,double param_3,double param_4,long *param_5,
           undefined8 param_6,undefined8 param_7,long param_8,int param_9,int param_10,
           undefined4 param_11)

{
  undefined4 uVar1;
  undefined4 uVar2;
  undefined4 uVar3;
  undefined4 uVar4;
  undefined4 uVar5;
  bool bVar6;
  char cVar7;
  int iVar8;
  int iVar9;
  int iVar10;
  undefined4 uVar11;
  double dVar12;
  double dVar13;
  double dVar14;
  double dVar15;
  double dVar16;
  double dVar17;
  double dVar18;
  double dVar19;
  double dVar20;
  double dVar21;
  float fVar22;
  double dVar23;
  double dVar24;
  double local_140;
  undefined8 local_138;
  undefined8 uStack_130;
  undefined8 local_128;
  undefined8 local_120;
  undefined8 uStack_118;
  undefined8 local_110;
  undefined8 uStack_108;
  undefined8 local_100;
  undefined8 local_f8;
  undefined8 local_f0;
  undefined8 uStack_e8;
  undefined8 uStack_e0;
  undefined8 uStack_d8;
  undefined8 local_d0;
  undefined8 local_c8;
  undefined8 local_c0;
  undefined8 local_b8;
  undefined4 local_b0;
  
  local_c0 = 0;
  local_b8 = 0;
  local_b0 = 0;
  local_d0 = 0;
  local_c8 = 0;
  uStack_108 = 0;
  local_110 = 0;
  local_f8 = 0;
  local_100 = 0;
  uStack_e8 = 0;
  local_f0 = 0;
  uStack_d8 = 0;
  uStack_e0 = 0;
  uStack_118 = 0;
  local_120 = 0;
  local_138 = 0;
  uStack_130 = 0;
  local_128 = 0;
  if (param_8 == 0) {
    fVar22 = 0.0;
  }
  else {
    fVar22 = *(float *)(param_8 + 0x30);
  }
  cVar7 = (**(code **)(*param_5 + 0x720))(param_5);
  local_140 = 0.0;
  if (cVar7 == '\0') {
    iVar8 = AndroidBitmap_getInfo(param_5,param_6,&local_c0);
    if ((iVar8 == 0) && (local_b8._4_4_ == 1)) {
      if ((uint)local_c0 != 0) {
        if ((((0x8000 < (uint)local_c0) || (local_c0._4_4_ - 0x8001U < 0xffff8000)) ||
            ((int)(uint)local_b8 < 0)) ||
           (((uint)local_b8 < (uint)local_c0 << 2 || (80000000 < local_c0._4_4_ * (uint)local_c0))))
        goto LAB_005870fc;
        iVar8 = AndroidBitmap_lockPixels(param_5,param_6,&local_c8);
        if (iVar8 == 0) {
          dVar16 = (double)b6_now_ms();
          if ((param_8 != 0) && (param_9 == 0)) {
            b8_estimate_cast(param_8,local_c8,local_c0 & 0xffffffff,local_c0._4_4_,
                             local_b8 & 0xffffffff,&local_120);
          }
          local_140 = (double)b6_now_ms();
          dVar20 = (double)b6_now_ms();
          if (param_10 == 4) {
            iVar8 = b4_m3_grade(local_c8,local_c0 & 0xffffffff,local_c0._4_4_,local_b8 & 0xffffffff)
            ;
            bVar6 = false;
            uVar11 = 1;
          }
          else if (param_10 == 2) {
            iVar8 = m9_b10_apply(fVar22,local_c8,local_c0 & 0xffffffff,local_c0._4_4_,
                                 local_b8 & 0xffffffff,&local_120,&local_138);
            uVar11 = 0;
            bVar6 = true;
          }
          else if (param_10 == 1) {
            iVar8 = b8_apply_cast(local_c8,local_c0 & 0xffffffff,local_c0._4_4_,
                                  local_b8 & 0xffffffff,&local_120);
            uVar11 = 0;
            bVar6 = false;
          }
          else {
            uVar11 = 0;
            bVar6 = false;
            iVar8 = 1;
          }
          dVar17 = (double)b6_now_ms();
          dVar12 = (double)b6_now_ms();
          if (bVar6) {
            iVar9 = b12_guard(fVar22);
          }
          else {
            iVar9 = b4_guard(param_7,local_c8,local_c0 & 0xffffffff,local_c0._4_4_,
                             local_b8 & 0xffffffff,param_9,uVar11,&local_f0);
          }
          local_140 = local_140 - dVar16;
          dVar17 = dVar17 - dVar20;
          dVar16 = (double)b6_now_ms();
          dVar16 = dVar16 - dVar12;
          iVar10 = AndroidBitmap_unlockPixels(param_5,param_6);
          if (iVar10 != 0) {
            iVar9 = 0;
            iVar8 = 0;
          }
          b4_free(param_7);
          goto joined_r0x00587454;
        }
      }
      goto LAB_00587048;
    }
LAB_005870fc:
    b4_free(param_7);
  }
  else {
LAB_00587048:
    b4_free(param_7);
  }
  dVar17 = 0.0;
  dVar16 = 0.0;
  iVar8 = 0;
  iVar9 = 0;
joined_r0x00587454:
  if ((param_10 == 2) && (bVar6 = (int)local_138 != 0, bVar6)) {
    local_138._4_4_ = (float)((ulong)local_138 >> 0x20);
    uStack_130._4_4_ = (float)((ulong)uStack_130 >> 0x20);
    local_128._4_4_ = (float)((ulong)local_128 >> 0x20);
    dVar20 = (double)local_138._4_4_;
    dVar12 = (double)(float)uStack_130;
    dVar13 = (double)uStack_130._4_4_;
    dVar14 = (double)(float)local_128;
    dVar15 = (double)local_128._4_4_;
    __android_log_print(dVar20,dVar12,dVar13,dVar14,dVar15,4,"LeicaM9M3B12",
                        "B12 look=M9_CLEAR_DENSITY_B12 applied=%d vignette=always nominalCornerEV=%.3f sampledCornerEV=%.3f sampledSideEV=%.3f centerEV=%.5f grainPeakEV=%.3f pixelOrder=LUT_vignette_grain_guard_HDR"
                       );
  }
  dVar20 = 0.0;
  if (((param_10 == 2) && (iVar8 != 0)) &&
     (cVar7 = (**(code **)(*param_5 + 0x720))(param_5), cVar7 == '\0')) {
    dVar12 = (double)b6_now_ms();
    b5_attach_hdr(param_5,param_6);
    dVar20 = (double)b6_now_ms();
    dVar20 = dVar20 - dVar12;
  }
  uVar5 = uStack_e0._4_4_;
  uVar1 = (undefined4)local_120;
  uVar2 = local_120._4_4_;
  uVar4 = local_f0._4_4_;
  uVar3 = (undefined4)uStack_118;
  dVar12 = (double)(float)uStack_e8;
  uVar11 = 4;
  if (iVar9 == 0 || iVar8 == 0) {
    uVar11 = 5;
  }
  dVar13 = (double)uStack_118._4_4_;
  dVar18 = (double)(float)local_110;
  dVar14 = (double)local_110._4_4_;
  dVar19 = (double)(float)local_100;
  dVar24 = (double)local_100._4_4_;
  dVar21 = (double)local_f8._4_4_;
  dVar23 = (double)(float)local_f8;
  dVar15 = (double)b6_now_ms();
  __android_log_print(dVar12,(double)fVar22,(double)param_1,dVar13,dVar18,dVar14,dVar19,dVar24,
                      uVar11,"LeicaM9M3B12",
                      "B12 stage=%d path=base_direct grade=%d guard=%d source_stage=%d paired=%d map_cells=%u maxChannelEV=%.3f cream=%.3f cct=%.0f cast=%d castConf=%.3f castR=%.3f castB=%.3f anchors=%u cells=%u inRG=%.3f inBG=%.3f outRG=%.3f outBG=%.3f snapshot_ms=%.2f upstream_ms=%.2f cast_estimate_ms=%.2f grade_ms=%.2f guard_ms=%.2f hdr_ms=%.2f native_total_ms=%.2f"
                      ,param_10,iVar8,iVar9,param_11,uVar5,uVar4,uVar1,uVar2,uVar3,dVar23,dVar21,
                      param_3 - param_2,param_4 - param_3,local_140,dVar17,dVar16,dVar20,
                      dVar15 - param_2);
  if (iVar8 == 0) {
    bVar6 = false;
  }
  else {
    cVar7 = (**(code **)(*param_5 + 0x720))(param_5);
    bVar6 = cVar7 == '\0';
  }
  return bVar6;
}



/* 0058745c Java_com_codex_lmoments_LegendaryPostProcessor_applyWarmOriginalFilter */

/* WARNING: Type propagation algorithm not settling */

undefined4
Java_com_codex_lmoments_LegendaryPostProcessor_applyWarmOriginalFilter
          (undefined4 param_1,float param_2,undefined4 param_3,undefined4 param_4,long *param_5,
          undefined8 param_6,undefined8 param_7,undefined8 param_8)

{
  long *plVar1;
  long lVar2;
  undefined8 uVar3;
  undefined8 uVar4;
  undefined8 uVar5;
  float fVar6;
  bool bVar7;
  char cVar8;
  int iVar9;
  undefined4 uVar10;
  void *__pointer;
  long lVar11;
  code *pcVar12;
  undefined8 uVar13;
  long lVar14;
  long local_98;
  
  cVar8 = (**(code **)(*param_5 + 0x720))();
  if (cVar8 != '\0') {
    return 0;
  }
  pthread_once((pthread_once_t *)&once,init_key);
  if (key_ok == 0) {
LAB_005875b8:
    __pointer = (void *)0x0;
    local_98 = 0;
    bVar7 = true;
    lVar11 = dlopen("libzxbase.so",2);
  }
  else {
    __pointer = pthread_getspecific(key);
    if (__pointer == (void *)0x0) {
      __pointer = calloc(1,0x18);
      if (__pointer != (void *)0x0) {
        iVar9 = (**(code **)(*param_5 + 0x6d8))(param_5,__pointer);
        if ((iVar9 == 0) && (iVar9 = pthread_setspecific(key,__pointer), iVar9 == 0))
        goto LAB_00587520;
        free(__pointer);
      }
      goto LAB_005875b8;
    }
LAB_00587520:
    local_98 = 0;
    if (*(long *)((long)__pointer + 8) != 0) {
      if (*(long *)((long)__pointer + 0x10) != 0) {
        cVar8 = (**(code **)(*param_5 + 0xc0))(param_5,*(long *)((long)__pointer + 8),param_7);
        if (cVar8 != '\0') {
          lVar14 = *(long *)((long)__pointer + 0x10);
          bVar7 = false;
          uVar10 = 1;
          lVar11 = dlopen("libzxbase.so",2);
          goto joined_r0x005875dc;
        }
        if (*(long *)((long)__pointer + 8) == 0) goto LAB_005877b0;
      }
      (**(code **)(*param_5 + 0x718))(param_5);
      *(undefined8 *)((long)__pointer + 8) = 0;
    }
LAB_005877b0:
    b8_color_free(*(undefined8 *)((long)__pointer + 0x10));
    bVar7 = false;
    *(undefined8 *)((long)__pointer + 0x10) = 0;
    lVar11 = dlopen("libzxbase.so",2);
  }
  uVar10 = 2;
  lVar14 = 0;
joined_r0x005875dc:
  if (lVar11 == 0) {
    __android_log_print(6,"LeicaM9M3B12","Required original library unavailable");
  }
  else {
    pcVar12 = (code *)dlsym(lVar11,
                            "Java_com_codex_lmoments_LegendaryPostProcessor_applyOriginalFilter");
    if (pcVar12 != (code *)0x0) {
      uVar3 = b6_now_ms();
      plVar1 = &local_98;
      if (lVar14 != 0) {
        plVar1 = (long *)0x0;
      }
      uVar13 = snapshot(param_1,param_2,param_5,param_7,0,plVar1);
      lVar2 = local_98;
      if (lVar14 != 0) {
        lVar2 = lVar14;
      }
      uVar4 = b6_now_ms();
      cVar8 = (**(code **)(*param_5 + 0x720))(param_5);
      if (cVar8 != '\0') {
        b4_free(uVar13);
        b8_color_free(local_98);
        if (!bVar7) {
          if (*(long *)((long)__pointer + 8) != 0) {
            (**(code **)(*param_5 + 0x718))(param_5);
            *(undefined8 *)((long)__pointer + 8) = 0;
          }
          b8_color_free(*(undefined8 *)((long)__pointer + 0x10));
          *(undefined8 *)((long)__pointer + 0x10) = 0;
        }
        dlclose(lVar11);
        return 0;
      }
      fVar6 = param_2;
      if (20000.0 < param_2 || (0x7f7fffff < ((uint)param_2 & 0x7fffffff) || param_2 < 1000.0)) {
        fVar6 = 5500.0;
      }
      cVar8 = (*pcVar12)(param_1,fVar6,param_3,param_4,param_5,param_6,param_7,param_8);
      uVar5 = b6_now_ms();
      if ((cVar8 == '\0') || (cVar8 = (**(code **)(*param_5 + 0x720))(param_5), cVar8 != '\0')) {
        b4_free(uVar13);
        __android_log_print(6,"LeicaM9M3B12",
                            "B12 upstream_failed stage=2 recovery=fresh_source_requested");
        uVar10 = 0;
        b8_color_free(local_98);
      }
      else {
        uVar10 = finish(param_2,uVar3,uVar4,uVar5,param_5,param_7,uVar13,lVar2,0,2,uVar10);
        b8_color_free(local_98);
      }
      if (!bVar7) {
        if (*(long *)((long)__pointer + 8) != 0) {
          (**(code **)(*param_5 + 0x718))(param_5);
          *(undefined8 *)((long)__pointer + 8) = 0;
        }
        b8_color_free(*(undefined8 *)((long)__pointer + 0x10));
        *(undefined8 *)((long)__pointer + 0x10) = 0;
      }
      dlclose(lVar11);
      return uVar10;
    }
    __android_log_print(6,"LeicaM9M3B12","Missing original entry: %s",
                        "Java_com_codex_lmoments_LegendaryPostProcessor_applyOriginalFilter");
    dlclose(lVar11);
  }
  if (bVar7) {
    return 0;
  }
  if (*(long *)((long)__pointer + 8) != 0) {
    (**(code **)(*param_5 + 0x718))(param_5);
    *(undefined8 *)((long)__pointer + 8) = 0;
  }
  b8_color_free(*(undefined8 *)((long)__pointer + 0x10));
  *(undefined8 *)((long)__pointer + 0x10) = 0;
  return 0;
}



/* 005878a0 Java_com_codex_lmoments_LegendaryPostProcessor_applyOriginalFilter */

undefined4
Java_com_codex_lmoments_LegendaryPostProcessor_applyOriginalFilter
          (undefined4 param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4,long *param_5
          ,undefined8 param_6,undefined8 param_7,undefined8 param_8)

{
  undefined8 uVar1;
  undefined8 uVar2;
  undefined8 uVar3;
  char cVar4;
  int iVar5;
  undefined4 uVar6;
  void *__pointer;
  long lVar7;
  code *pcVar8;
  undefined8 uVar9;
  
  cVar4 = (**(code **)(*param_5 + 0x720))();
  if (cVar4 != '\0') {
    return 0;
  }
  pthread_once((pthread_once_t *)&once,init_key);
  if (key_ok == 0) goto LAB_005879a4;
  __pointer = pthread_getspecific(key);
  if (__pointer == (void *)0x0) {
    __pointer = calloc(1,0x18);
    if (__pointer == (void *)0x0) goto LAB_005879a4;
    iVar5 = (**(code **)(*param_5 + 0x6d8))(param_5,__pointer);
    if ((iVar5 != 0) || (iVar5 = pthread_setspecific(key,__pointer), iVar5 != 0)) {
      free(__pointer);
      goto LAB_005879a4;
    }
  }
  if (*(long *)((long)__pointer + 8) != 0) {
    (**(code **)(*param_5 + 0x718))(param_5);
    *(undefined8 *)((long)__pointer + 8) = 0;
  }
  b8_color_free(*(undefined8 *)((long)__pointer + 0x10));
  *(undefined8 *)((long)__pointer + 0x10) = 0;
LAB_005879a4:
  lVar7 = dlopen("libzxbase.so",2);
  if (lVar7 == 0) {
    __android_log_print(6,"LeicaM9M3B12","Required original library unavailable");
  }
  else {
    pcVar8 = (code *)dlsym(lVar7,
                           "Java_com_codex_lmoments_LegendaryPostProcessor_applyOriginalFilter");
    if (pcVar8 == (code *)0x0) {
      __android_log_print(6,"LeicaM9M3B12","Missing original entry: %s",
                          "Java_com_codex_lmoments_LegendaryPostProcessor_applyOriginalFilter");
    }
    else {
      uVar1 = b6_now_ms();
      uVar9 = snapshot(param_1,param_2,param_5,param_7,1,0);
      uVar2 = b6_now_ms();
      cVar4 = (**(code **)(*param_5 + 0x720))(param_5);
      if (cVar4 == '\0') {
        cVar4 = (*pcVar8)(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8);
        if ((cVar4 == '\0') || (cVar4 = (**(code **)(*param_5 + 0x720))(param_5), cVar4 != '\0')) {
          b4_free(uVar9);
          uVar6 = 0;
        }
        else {
          uVar3 = b6_now_ms();
          uVar6 = finish(param_2,uVar1,uVar2,uVar3,param_5,param_7,uVar9,0,1,3,0);
        }
        dlclose(lVar7);
        return uVar6;
      }
      b4_free(uVar9);
    }
    dlclose(lVar7);
  }
  return 0;
}



/* 00587b30 Java_com_codex_lmoments_LegendaryPostProcessor_applyMonochrome */

undefined4
Java_com_codex_lmoments_LegendaryPostProcessor_applyMonochrome
          (long *param_1,undefined8 param_2,undefined8 param_3,undefined8 param_4,undefined8 param_5
          )

{
  undefined8 uVar1;
  undefined8 uVar2;
  undefined8 uVar3;
  char cVar4;
  int iVar5;
  undefined4 uVar6;
  void *__pointer;
  long lVar7;
  code *pcVar8;
  undefined8 uVar9;
  
  cVar4 = (**(code **)(*param_1 + 0x720))();
  if (cVar4 != '\0') {
    return 0;
  }
  pthread_once((pthread_once_t *)&once,init_key);
  if (key_ok == 0) goto LAB_00587c20;
  __pointer = pthread_getspecific(key);
  if (__pointer == (void *)0x0) {
    __pointer = calloc(1,0x18);
    if (__pointer == (void *)0x0) goto LAB_00587c20;
    iVar5 = (**(code **)(*param_1 + 0x6d8))(param_1,__pointer);
    if ((iVar5 != 0) || (iVar5 = pthread_setspecific(key,__pointer), iVar5 != 0)) {
      free(__pointer);
      goto LAB_00587c20;
    }
  }
  if (*(long *)((long)__pointer + 8) != 0) {
    (**(code **)(*param_1 + 0x718))(param_1);
    *(undefined8 *)((long)__pointer + 8) = 0;
  }
  b8_color_free(*(undefined8 *)((long)__pointer + 0x10));
  *(undefined8 *)((long)__pointer + 0x10) = 0;
LAB_00587c20:
  lVar7 = dlopen("libzxbase.so",2);
  if (lVar7 == 0) {
    __android_log_print(6,"LeicaM9M3B12","Required original library unavailable");
  }
  else {
    pcVar8 = (code *)dlsym(lVar7,"Java_com_codex_lmoments_LegendaryPostProcessor_applyMonochrome");
    if (pcVar8 == (code *)0x0) {
      __android_log_print(6,"LeicaM9M3B12","Missing original entry: %s",
                          "Java_com_codex_lmoments_LegendaryPostProcessor_applyMonochrome");
    }
    else {
      uVar1 = b6_now_ms();
      uVar9 = snapshot(0xbf800000,0xbf800000,param_1,param_3,1,0);
      uVar2 = b6_now_ms();
      cVar4 = (**(code **)(*param_1 + 0x720))(param_1);
      if (cVar4 == '\0') {
        cVar4 = (*pcVar8)(param_1,param_2,param_3,param_4,param_5);
        if ((cVar4 == '\0') || (cVar4 = (**(code **)(*param_1 + 0x720))(param_1), cVar4 != '\0')) {
          b4_free(uVar9);
          uVar6 = 0;
        }
        else {
          uVar3 = b6_now_ms();
          uVar6 = finish(0xbf800000,uVar1,uVar2,uVar3,param_1,param_3,uVar9,0,1,4,0);
        }
        dlclose(lVar7);
        return uVar6;
      }
      b4_free(uVar9);
    }
    dlclose(lVar7);
  }
  return 0;
}



/* 00587d98 init_key */

void init_key(void)

{
  int iVar1;
  
  iVar1 = pthread_key_create(&key,destroy_frame);
  key_ok = (uint)(iVar1 == 0);
  return;
}



/* 00587dd4 destroy_frame */

void destroy_frame(long **param_1)

{
  bool bVar1;
  int iVar2;
  long *plVar3;
  long *local_28;
  
  if (param_1 != (long **)0x0) {
    plVar3 = *param_1;
    local_28 = (long *)0x0;
    if ((plVar3 == (long *)0x0) || (param_1[1] == (long *)0x0)) {
      b8_color_free(param_1[2]);
    }
    else {
      iVar2 = (**(code **)(*plVar3 + 0x30))(plVar3,&local_28,0x10006);
      if (iVar2 == -2) {
        iVar2 = (**(code **)(**param_1 + 0x20))(*param_1,&local_28,0);
        bVar1 = iVar2 != 0;
      }
      else {
        bVar1 = true;
      }
      if (local_28 != (long *)0x0) {
        (**(code **)(*local_28 + 0x718))(local_28,param_1[1]);
      }
      b8_color_free(param_1[2]);
      if (!bVar1) {
        (**(code **)(**param_1 + 0x28))();
      }
    }
    free(param_1);
  }
  return;
}



/* 00587ea8 Java_com_codex_lmoments_RenderQueue_enter */

undefined8 Java_com_codex_lmoments_RenderQueue_enter(long *param_1,undefined8 param_2,long param_3)

{
  char cVar1;
  int iVar2;
  long lVar3;
  long lVar4;
  long lVar5;
  long lVar6;
  long lVar7;
  long lVar8;
  long lVar9;
  undefined8 uVar10;
  long lVar11;
  double dVar12;
  double dVar13;
  
  iVar2 = (**(code **)(*param_1 + 0x98))(param_1,0x18);
  if (iVar2 < 0) {
    return 0;
  }
  dVar12 = (double)b6_now_ms();
  lVar3 = (**(code **)(*param_1 + 0xf8))(param_1,param_2);
  cVar1 = (**(code **)(*param_1 + 0x720))(param_1);
  lVar11 = 0;
  if ((cVar1 != '\0') || (lVar3 == 0)) goto LAB_005883ac;
  lVar4 = (**(code **)(*param_1 + 0x2f0))
                    (param_1,lVar3,"renderer","Ljava/util/concurrent/Semaphore;");
  cVar1 = (**(code **)(*param_1 + 0x720))(param_1);
  lVar11 = 0;
  if ((cVar1 != '\0') || (lVar4 == 0)) goto LAB_005883ac;
  lVar5 = (**(code **)(*param_1 + 0x2f0))(param_1,lVar3,"bytes",&DAT_0057649e);
  cVar1 = (**(code **)(*param_1 + 0x720))(param_1);
  lVar11 = 0;
  if ((cVar1 != '\0') || (lVar5 == 0)) goto LAB_005883ac;
  lVar6 = (**(code **)(*param_1 + 0x2f0))(param_1,lVar3,&DAT_00576505,&DAT_00576538);
  cVar1 = (**(code **)(*param_1 + 0x720))(param_1);
  lVar11 = 0;
  if ((cVar1 != '\0') || (lVar6 == 0)) goto LAB_005883ac;
  lVar3 = (**(code **)(*param_1 + 0x2f0))(param_1,lVar3,"byteLimit",&DAT_0057649e);
  cVar1 = (**(code **)(*param_1 + 0x720))(param_1);
  lVar11 = 0;
  if ((cVar1 != '\0') || (lVar3 == 0)) goto LAB_005883ac;
  lVar3 = (**(code **)(*param_1 + 0x328))(param_1,param_2,lVar3);
  cVar1 = (**(code **)(*param_1 + 0x720))(param_1);
  if (cVar1 == '\0') {
    if ((param_3 < 0) || (lVar3 < param_3)) {
      __android_log_print(6,"LeicaM9M3B12","B8 queue invalid single input bytes=%lld limit=%lld",
                          param_3,lVar3);
    }
    else {
      lVar3 = (**(code **)(*param_1 + 0x2f8))(param_1,param_2,lVar4);
      cVar1 = (**(code **)(*param_1 + 0x720))(param_1);
      lVar11 = 0;
      if ((cVar1 != '\0') || (lVar3 == 0)) goto LAB_005883ac;
      lVar4 = (**(code **)(*param_1 + 0xf8))(param_1,lVar3);
      cVar1 = (**(code **)(*param_1 + 0x720))(param_1);
      lVar11 = 0;
      if ((cVar1 != '\0') || (lVar4 == 0)) goto LAB_005883ac;
      lVar7 = (**(code **)(*param_1 + 0x108))(param_1,lVar4,"acquire",&DAT_00575994);
      cVar1 = (**(code **)(*param_1 + 0x720))(param_1);
      lVar11 = 0;
      if ((cVar1 != '\0') || (lVar7 == 0)) goto LAB_005883ac;
      lVar4 = (**(code **)(*param_1 + 0x108))(param_1,lVar4,"release",&DAT_00575994);
      cVar1 = (**(code **)(*param_1 + 0x720))(param_1);
      lVar11 = 0;
      if ((cVar1 != '\0') || (lVar4 == 0)) goto LAB_005883ac;
      lVar8 = (**(code **)(*param_1 + 0x30))(param_1,"com/codex/lmoments/RenderQueue$Ticket");
      cVar1 = (**(code **)(*param_1 + 0x720))(param_1);
      lVar11 = 0;
      if ((cVar1 != '\0') || (lVar8 == 0)) goto LAB_005883ac;
      lVar9 = (**(code **)(*param_1 + 0x108))
                        (param_1,lVar8,"<init>","(Lcom/codex/lmoments/RenderQueue;J)V");
      cVar1 = (**(code **)(*param_1 + 0x720))(param_1);
      lVar11 = 0;
      if ((cVar1 != '\0') || (lVar9 == 0)) goto LAB_005883ac;
      (**(code **)(*param_1 + 0x1e8))(param_1,lVar3,lVar7);
      cVar1 = (**(code **)(*param_1 + 0x720))(param_1);
      if (cVar1 != '\0') goto LAB_005883a8;
      lVar11 = (**(code **)(*param_1 + 0xe0))(param_1,lVar8,lVar9,param_2,param_3);
      cVar1 = (**(code **)(*param_1 + 0x720))(param_1);
      if (((cVar1 == '\0') && (lVar11 != 0)) &&
         (iVar2 = (**(code **)(*param_1 + 0x6c8))(param_1,param_2), iVar2 == 0)) {
        iVar2 = (**(code **)(*param_1 + 800))(param_1,param_2,lVar6);
        lVar7 = (**(code **)(*param_1 + 0x328))(param_1,param_2,lVar5);
        cVar1 = (**(code **)(*param_1 + 0x720))(param_1);
        if (cVar1 == '\0') {
          (**(code **)(*param_1 + 0x368))(param_1,param_2,lVar6,iVar2 + 1);
          (**(code **)(*param_1 + 0x370))(param_1,param_2,lVar5,lVar7 + param_3);
          cVar1 = (**(code **)(*param_1 + 0x720))(param_1);
          if (cVar1 == '\0') {
            (**(code **)(*param_1 + 0x6d0))(param_1,param_2);
            cVar1 = (**(code **)(*param_1 + 0x720))(param_1);
            if (cVar1 == '\0') {
              dVar13 = (double)b6_now_ms();
              __android_log_print(dVar13 - dVar12,4,"LeicaM9M3B12",
                                  "B8 queue admitted bytes=%lld queue_wait_ms=%.2f active=1 no_busy_style_bypass=1"
                                  ,param_3);
              goto LAB_005883ac;
            }
            goto LAB_00588350;
          }
        }
        (**(code **)(*param_1 + 0x6d0))(param_1,param_2);
      }
LAB_00588350:
      cleanup_call(param_1,lVar3,lVar4);
    }
  }
LAB_005883a8:
  lVar11 = 0;
LAB_005883ac:
                    /* WARNING: Could not recover jumptable at 0x005883d4. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  uVar10 = (**(code **)(*param_1 + 0xa0))(param_1,lVar11);
  return uVar10;
}



/* 00588430 cleanup_call */

void cleanup_call(long *param_1,long param_2,long param_3)

{
  char cVar1;
  long lVar2;
  
  if ((param_2 != 0) && (param_3 != 0)) {
    lVar2 = (**(code **)(*param_1 + 0x78))();
    if (lVar2 != 0) {
      (**(code **)(*param_1 + 0x88))(param_1);
      (**(code **)(*param_1 + 0x1e8))(param_1,param_2,param_3);
      (**(code **)(*param_1 + 0x720))(param_1);
      cVar1 = (**(code **)(*param_1 + 0x720))(param_1);
      if (cVar1 != '\0') {
        (**(code **)(*param_1 + 0x88))(param_1);
      }
      (**(code **)(*param_1 + 0x68))(param_1,lVar2);
                    /* WARNING: Could not recover jumptable at 0x005884f8. Too many branches */
                    /* WARNING: Treating indirect jump as call */
      (**(code **)(*param_1 + 0xb8))(param_1,lVar2);
      return;
    }
    (**(code **)(*param_1 + 0x1e8))(param_1,param_2,param_3);
                    /* WARNING: Could not recover jumptable at 0x00588538. Too many branches */
                    /* WARNING: Treating indirect jump as call */
    (**(code **)(*param_1 + 0x720))(param_1);
    return;
  }
  return;
}



/* 0058853c Java_com_codex_lmoments_JpegMetadata_copyExif___3B_3BZ */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

long Java_com_codex_lmoments_JpegMetadata_copyExif___3B_3BZ
               (long *param_1,undefined8 param_2,long param_3,undefined8 param_4,char param_5)

{
  bool bVar1;
  undefined auVar2 [16];
  ulong uVar3;
  undefined4 uVar4;
  char cVar5;
  char cVar6;
  int iVar7;
  int iVar8;
  undefined4 uVar9;
  long lVar10;
  long lVar11;
  long lVar12;
  undefined8 uVar13;
  long lVar14;
  long lVar15;
  long lVar16;
  long lVar17;
  long lVar18;
  undefined *puVar19;
  long lVar20;
  long lVar21;
  char *pcVar22;
  char *pcVar23;
  char *pcVar24;
  uint uVar25;
  double dVar26;
  double dVar27;
  byte bVar32;
  undefined auVar29 [16];
  undefined auVar30 [16];
  undefined auVar31 [16];
  undefined auVar33 [16];
  undefined8 local_c0;
  undefined8 uStack_b8;
  undefined8 uStack_b0;
  undefined8 uStack_a8;
  undefined8 local_a0;
  undefined8 local_90;
  undefined8 local_88;
  undefined4 local_80;
  undefined8 local_68;
  undefined auVar28 [12];
  
  cVar5 = (**(code **)(*param_1 + 0xc0))(param_1,param_3,param_4);
  if (cVar5 == '\0') {
    lVar10 = (**(code **)(*param_1 + 0x388))(param_1,param_2,"copyExif","([B[BZII)[B");
    cVar5 = (**(code **)(*param_1 + 0x720))(param_1);
    if (cVar5 != '\0') {
      return 0;
    }
    if (lVar10 == 0) {
      return 0;
    }
                    /* WARNING: Could not recover jumptable at 0x005887c0. Too many branches */
                    /* WARNING: Treating indirect jump as call */
    lVar10 = (**(code **)(*param_1 + 0x390))(param_1,param_2,lVar10,param_3,param_4,param_5,0,0);
    return lVar10;
  }
  iVar7 = (**(code **)(*param_1 + 0x98))(param_1,0x40);
  if (iVar7 < 0) {
    (**(code **)(*param_1 + 0x88))(param_1);
    __android_log_print(6,"LeicaM9M3B12","B8 recovery cannot allocate JNI frame; source_retained=1")
    ;
    return param_3;
  }
  local_68 = 0;
  dVar26 = (double)b6_now_ms();
  if (param_3 == 0) {
    lVar20 = 0;
    lVar21 = 0;
    lVar12 = 0;
    lVar11 = 0;
    lVar10 = 0;
    pcVar24 = "input";
    bVar1 = true;
    goto LAB_0058911c;
  }
  iVar7 = (**(code **)(*param_1 + 0x558))(param_1,param_3);
  cVar5 = (**(code **)(*param_1 + 0x720))(param_1);
  pcVar22 = "input";
  if ((cVar5 == '\0') && (0xfa000002 < iVar7 + 0xf9ffffffU)) {
    lVar10 = (**(code **)(*param_1 + 0x30))(param_1,"android/os/Looper");
    cVar5 = (**(code **)(*param_1 + 0x720))(param_1);
    pcVar23 = "thread check";
    pcVar22 = "thread check";
    if ((cVar5 != '\0') || (lVar10 == 0)) goto LAB_0058910c;
    lVar11 = (**(code **)(*param_1 + 0x388))(param_1,lVar10,"myLooper","()Landroid/os/Looper;");
    cVar5 = (**(code **)(*param_1 + 0x720))(param_1);
    if ((cVar5 != '\0') || (lVar11 == 0)) goto LAB_0058910c;
    lVar12 = (**(code **)(*param_1 + 0x388))(param_1,lVar10,"getMainLooper","()Landroid/os/Looper;")
    ;
    cVar5 = (**(code **)(*param_1 + 0x720))(param_1);
    if ((cVar5 != '\0') || (lVar12 == 0)) {
LAB_00589514:
      lVar12 = 0;
      pcVar24 = pcVar23;
      goto LAB_0058951c;
    }
    uVar13 = (**(code **)(*param_1 + 0x390))(param_1,lVar10,lVar11);
    cVar5 = (**(code **)(*param_1 + 0x720))(param_1);
    if (cVar5 == '\0') {
      lVar10 = (**(code **)(*param_1 + 0x390))(param_1,lVar10,lVar12);
      cVar5 = (**(code **)(*param_1 + 0x720))(param_1);
      if (cVar5 == '\0') {
        if ((lVar10 == 0) ||
           (cVar5 = (**(code **)(*param_1 + 0xc0))(param_1,uVar13,lVar10), cVar5 == '\0')) {
          lVar10 = (**(code **)(*param_1 + 0x30))
                             (param_1,"com/codex/lmoments/LegendaryPostProcessor");
          cVar5 = (**(code **)(*param_1 + 0x720))(param_1);
          pcVar24 = "queue";
          pcVar23 = "queue";
          pcVar22 = pcVar23;
          if ((cVar5 == '\0') && (lVar10 != 0)) {
            lVar11 = (**(code **)(*param_1 + 0x480))
                               (param_1,lVar10,"renderQueue","Lcom/codex/lmoments/RenderQueue;");
            cVar5 = (**(code **)(*param_1 + 0x720))(param_1);
            if ((cVar5 == '\0') && (lVar11 != 0)) {
              lVar10 = (**(code **)(*param_1 + 0x488))(param_1,lVar10,lVar11);
              cVar5 = (**(code **)(*param_1 + 0x720))(param_1);
              if ((cVar5 == '\0') && (lVar10 != 0)) {
                lVar11 = (**(code **)(*param_1 + 0xf8))(param_1,lVar10);
                cVar5 = (**(code **)(*param_1 + 0x720))(param_1);
                if ((cVar5 == '\0') && (lVar11 != 0)) {
                  lVar11 = (**(code **)(*param_1 + 0x108))
                                     (param_1,lVar11,"enter",
                                      "(J)Lcom/codex/lmoments/RenderQueue$Ticket;");
                  cVar5 = (**(code **)(*param_1 + 0x720))(param_1);
                  if ((cVar5 != '\0') || (lVar11 == 0)) goto LAB_00589514;
                  lVar12 = (**(code **)(*param_1 + 0x110))(param_1,lVar10,lVar11,iVar7);
                  cVar5 = (**(code **)(*param_1 + 0x720))(param_1);
                  if ((cVar5 == '\0') && (lVar12 != 0)) {
                    lVar10 = (**(code **)(*param_1 + 0xf8))(param_1,lVar12);
                    cVar5 = (**(code **)(*param_1 + 0x720))(param_1);
                    if ((cVar5 == '\0') && (lVar10 != 0)) {
                      lVar20 = (**(code **)(*param_1 + 0x108))(param_1,lVar10,"close",&DAT_00575994)
                      ;
                      cVar5 = (**(code **)(*param_1 + 0x720))(param_1);
                      if ((cVar5 == '\0') && (lVar20 != 0)) {
                        lVar18 = (**(code **)(*param_1 + 0x30))(param_1,"android/graphics/Bitmap");
                        cVar5 = (**(code **)(*param_1 + 0x720))(param_1);
                        pcVar23 = "decode";
                        pcVar24 = "decode";
                        if ((cVar5 == '\0') && (lVar18 != 0)) {
                          lVar21 = (**(code **)(*param_1 + 0x108))
                                             (param_1,lVar18,"recycle",&DAT_00575994);
                          cVar5 = (**(code **)(*param_1 + 0x720))(param_1);
                          if ((cVar5 == '\0') && (lVar21 != 0)) {
                            lVar10 = (**(code **)(*param_1 + 0x30))
                                               (param_1,"android/graphics/BitmapFactory$Options");
                            cVar5 = (**(code **)(*param_1 + 0x720))(param_1);
                            if ((cVar5 == '\0') && (lVar10 != 0)) {
                              lVar11 = (**(code **)(*param_1 + 0x108))
                                                 (param_1,lVar10,"<init>",&DAT_00575994);
                              cVar5 = (**(code **)(*param_1 + 0x720))(param_1);
                              if ((cVar5 == '\0') && (lVar11 != 0)) {
                                lVar11 = (**(code **)(*param_1 + 0xe0))(param_1,lVar10,lVar11);
                                cVar5 = (**(code **)(*param_1 + 0x720))(param_1);
                                if ((cVar5 == '\0') && (lVar11 != 0)) {
                                  lVar14 = (**(code **)(*param_1 + 0x2f0))
                                                     (param_1,lVar10,"inMutable",&DAT_00576125);
                                  cVar5 = (**(code **)(*param_1 + 0x720))(param_1);
                                  if ((cVar5 == '\0') && (lVar14 != 0)) {
                                    (**(code **)(*param_1 + 0x348))(param_1,lVar11,lVar14,1);
                                    lVar14 = (**(code **)(*param_1 + 0x30))
                                                       (param_1,"android/graphics/Bitmap$Config");
                                    cVar5 = (**(code **)(*param_1 + 0x720))(param_1);
                                    if ((cVar5 == '\0') && (lVar14 != 0)) {
                                      lVar15 = (**(code **)(*param_1 + 0x480))
                                                         (param_1,lVar14,"ARGB_8888",
                                                          "Landroid/graphics/Bitmap$Config;");
                                      cVar5 = (**(code **)(*param_1 + 0x720))(param_1);
                                      if ((cVar5 == '\0') && (lVar15 != 0)) {
                                        lVar14 = (**(code **)(*param_1 + 0x488))
                                                           (param_1,lVar14,lVar15);
                                        cVar5 = (**(code **)(*param_1 + 0x720))(param_1);
                                        if ((cVar5 == '\0') && (lVar14 != 0)) {
                                          lVar15 = (**(code **)(*param_1 + 0x2f0))
                                                             (param_1,lVar10,"inPreferredConfig",
                                                              "Landroid/graphics/Bitmap$Config;");
                                          cVar5 = (**(code **)(*param_1 + 0x720))(param_1);
                                          if ((cVar5 == '\0') && (lVar15 != 0)) {
                                            (**(code **)(*param_1 + 0x340))
                                                      (param_1,lVar11,lVar15,lVar14);
                                            lVar15 = (**(code **)(*param_1 + 0x30))
                                                               (param_1,
                                                  "android/graphics/ColorSpace");
                                            cVar5 = (**(code **)(*param_1 + 0x720))(param_1);
                                            if ((cVar5 == '\0') && (lVar15 != 0)) {
                                              lVar16 = (**(code **)(*param_1 + 0x30))
                                                                 (param_1,
                                                  "android/graphics/ColorSpace$Named");
                                              cVar5 = (**(code **)(*param_1 + 0x720))(param_1);
                                              if ((cVar5 == '\0') && (lVar16 != 0)) {
                                                pcVar22 = "DISPLAY_P3";
                                                if (param_5 != '\0') {
                                                  pcVar22 = "SRGB";
                                                }
                                                lVar17 = (**(code **)(*param_1 + 0x480))
                                                                   (param_1,lVar16,pcVar22,
                                                                                                                                        
                                                  "Landroid/graphics/ColorSpace$Named;");
                                                cVar5 = (**(code **)(*param_1 + 0x720))(param_1);
                                                if ((cVar5 == '\0') && (lVar17 != 0)) {
                                                  lVar16 = (**(code **)(*param_1 + 0x488))
                                                                     (param_1,lVar16,lVar17);
                                                  cVar5 = (**(code **)(*param_1 + 0x720))(param_1);
                                                  if ((cVar5 == '\0') && (lVar16 != 0)) {
                                                    lVar17 = (**(code **)(*param_1 + 0x388))
                                                                       (param_1,lVar15,&DAT_00575d92
                                                                        ,
                                                  "(Landroid/graphics/ColorSpace$Named;)Landroid/graphics/ColorSpace;"
                                                  );
                                                  cVar5 = (**(code **)(*param_1 + 0x720))(param_1);
                                                  if ((cVar5 == '\0') && (lVar17 != 0)) {
                                                    lVar15 = (**(code **)(*param_1 + 0x390))
                                                                       (param_1,lVar15,lVar17,lVar16
                                                                       );
                                                    cVar5 = (**(code **)(*param_1 + 0x720))(param_1)
                                                    ;
                                                    if ((cVar5 == '\0') && (lVar15 != 0)) {
                                                      lVar10 = (**(code **)(*param_1 + 0x2f0))
                                                                         (param_1,lVar10,
                                                                          "inPreferredColorSpace",
                                                                                                                                                    
                                                  "Landroid/graphics/ColorSpace;");
                                                  cVar5 = (**(code **)(*param_1 + 0x720))(param_1);
                                                  if ((cVar5 == '\0') && (lVar10 != 0)) {
                                                    (**(code **)(*param_1 + 0x340))
                                                              (param_1,lVar11,lVar10,lVar15);
                                                    cVar5 = (**(code **)(*param_1 + 0x720))(param_1)
                                                    ;
                                                    if (cVar5 != '\0') goto LAB_00588724;
                                                    lVar10 = (**(code **)(*param_1 + 0x30))
                                                                       (param_1,
                                                  "android/graphics/BitmapFactory");
                                                  cVar5 = (**(code **)(*param_1 + 0x720))(param_1);
                                                  if ((cVar5 == '\0') && (lVar10 != 0)) {
                                                    lVar16 = (**(code **)(*param_1 + 0x388))
                                                                       (param_1,lVar10,
                                                                        "decodeByteArray",
                                                                                                                                                
                                                  "([BIILandroid/graphics/BitmapFactory$Options;)Landroid/graphics/Bitmap;"
                                                  );
                                                  cVar5 = (**(code **)(*param_1 + 0x720))(param_1);
                                                  if ((cVar5 == '\0') && (lVar16 != 0)) {
                                                    lVar10 = (**(code **)(*param_1 + 0x390))
                                                                       (param_1,lVar10,lVar16,
                                                                        param_3,0,iVar7,lVar11);
                                                    cVar5 = (**(code **)(*param_1 + 0x720))(param_1)
                                                    ;
                                                    lVar11 = 0;
                                                    pcVar24 = pcVar23;
                                                    if ((cVar5 == '\0') && (lVar10 != 0)) {
                                                      lVar11 = convert_space(param_1,lVar10,lVar15,
                                                                             lVar14,lVar18);
                                                      cVar5 = (**(code **)(*param_1 + 0x720))
                                                                        (param_1);
                                                      pcVar22 = "working colour space";
                                                      pcVar23 = "working colour space";
                                                      pcVar24 = pcVar23;
                                                      if ((cVar5 == '\0') && (lVar11 != 0)) {
                                                        cVar5 = (**(code **)(*param_1 + 0xc0))
                                                                          (param_1,lVar10,lVar11);
                                                        if (cVar5 == '\0') {
                                                          cleanup_call(param_1,lVar10,lVar21);
                                                          lVar10 = lVar11;
                                                        }
                                                        lVar11 = (**(code **)(*param_1 + 0x30))
                                                                           (param_1,
                                                  "com/codex/lmoments/HdrGainmaps");
                                                  cVar5 = (**(code **)(*param_1 + 0x720))(param_1);
                                                  pcVar24 = pcVar22;
                                                  if ((cVar5 == '\0') && (lVar11 != 0)) {
                                                    lVar14 = (**(code **)(*param_1 + 0x388))
                                                                       (param_1,lVar11,"attach",
                                                                                                                                                
                                                  "(Landroid/graphics/Bitmap;Landroid/graphics/Gainmap;)V"
                                                  );
                                                  cVar5 = (**(code **)(*param_1 + 0x720))(param_1);
                                                  pcVar24 = pcVar23;
                                                  if ((cVar5 == '\0') && (lVar14 != 0)) {
                                                    (**(code **)(*param_1 + 0x468))
                                                              (param_1,lVar11,lVar14,lVar10,0);
                                                    cVar5 = (**(code **)(*param_1 + 0x720))(param_1)
                                                    ;
                                                    pcVar24 = pcVar22;
                                                    if (cVar5 == '\0') {
                                                      local_90 = 0;
                                                      local_88 = 0;
                                                      local_80 = 0;
                                                      iVar8 = AndroidBitmap_getInfo
                                                                        (param_1,lVar10,&local_90);
                                                      pcVar22 = "fallback grade";
                                                      pcVar23 = "fallback grade";
                                                      pcVar24 = pcVar22;
                                                      if (iVar8 == 0) {
                                                        auVar29._8_8_ = 0x800000008000;
                                                        auVar29._0_8_ = local_90;
                                                        auVar30._8_8_ = 0;
                                                        auVar30._0_8_ = local_90;
                                                        auVar33 = NEON_cmeq(auVar30 << 0x40,auVar29,
                                                                            4);
                                                        auVar2._8_8_ = 0;
                                                        auVar2._0_8_ = local_90;
                                                        auVar30 = NEON_cmhi(auVar2 << 0x40,auVar29,4
                                                                           );
                                                        uVar25 = (uint)(byte)(auVar33[0] &
                                                                             (byte)_DAT_005497a0);
                                                        auVar28._0_8_ =
                                                             CONCAT17((byte)(auVar33._4_2_ >> 0xf) &
                                                                      (byte)((ulong)_DAT_005497a0 >>
                                                                            0x38),
                                                                      (uint7)CONCAT14(auVar33[4] &
                                                                                      (byte)((ulong)
                                                  _DAT_005497a0 >> 0x20),uVar25));
                                                  auVar28[8] = auVar30[8] & (byte)_UNK_005497a8;
                                                  auVar28[9] = auVar30[9] &
                                                               (byte)((ulong)_UNK_005497a8 >> 8);
                                                  bVar32 = (byte)((int)CONCAT13(auVar30[9],
                                                                                CONCAT12(auVar30[8],
                                                                                         auVar33.
                                                  _4_2_)) >> 0x1f);
                                                  auVar28[10] = bVar32 & (byte)((ulong)_UNK_005497a8
                                                                               >> 0x10);
                                                  auVar28[11] = bVar32 & (byte)((ulong)_UNK_005497a8
                                                                               >> 0x18);
                                                  auVar33[12] = auVar30[12] &
                                                                (byte)((ulong)_UNK_005497a8 >> 0x20)
                                                  ;
                                                  auVar33._0_12_ = auVar28;
                                                  auVar33[13] = auVar30[13] &
                                                                (byte)((ulong)_UNK_005497a8 >> 0x28)
                                                  ;
                                                  bVar32 = (char)auVar30[13] >> 7;
                                                  auVar33[14] = bVar32 & (byte)((ulong)_UNK_005497a8
                                                                               >> 0x30);
                                                  auVar33[15] = bVar32 & (byte)((ulong)_UNK_005497a8
                                                                               >> 0x38);
                                                  pcVar24 = pcVar23;
                                                  if (((((uVar25 + (int)((ulong)auVar28._0_8_ >>
                                                                        0x20) +
                                                          auVar28._8_4_ + auVar33._12_4_ & 0xf) == 0
                                                        ) && (local_88._4_4_ == 1)) &&
                                                      ((uint)((int)local_90 << 2) <= (uint)local_88)
                                                      ) && ((-1 < (int)(uint)local_88 &&
                                                            (iVar8 = AndroidBitmap_lockPixels
                                                                               (param_1,lVar10,
                                                                                &local_68),
                                                            pcVar24 = pcVar22, iVar8 == 0)))) {
                                                    if (param_5 == '\0') {
                                                      iVar8 = m9_b5_apply(ZEXT816(0xbf800000),0,
                                                                          local_68,local_90 &
                                                                                   0xffffffff,
                                                                          local_90._4_4_,
                                                                          local_88 & 0xffffffff,0);
                                                    }
                                                    else {
                                                      iVar8 = b4_m3_grade();
                                                    }
                                                    local_a0 = 0;
                                                    uStack_b8 = 0;
                                                    local_c0 = 0;
                                                    uStack_a8 = 0;
                                                    uStack_b0 = 0;
                                                    if (iVar8 == 0) {
                                                      AndroidBitmap_unlockPixels(param_1,lVar10);
                                                      pcVar24 = pcVar23;
                                                    }
                                                    else {
                                                      uVar9 = b4_guard(0,local_68,
                                                                       local_90 & 0xffffffff,
                                                                       local_90._4_4_,
                                                                       local_88 & 0xffffffff,param_5
                                                                       ,1,&local_c0);
                                                      iVar8 = AndroidBitmap_unlockPixels
                                                                        (param_1,lVar10);
                                                      if (iVar8 == 0) {
                                                        if (param_5 == '\0') {
                                                          b5_attach_hdr(param_1,lVar10);
                                                        }
                                                        cVar5 = (**(code **)(*param_1 + 0x720))
                                                                          (param_1);
                                                        pcVar24 = pcVar23;
                                                        if (cVar5 == '\0') {
                                                          lVar11 = (**(code **)(*param_1 + 0x30))
                                                                             (param_1,
                                                  "java/io/ByteArrayOutputStream");
                                                  cVar5 = (**(code **)(*param_1 + 0x720))(param_1);
                                                  pcVar24 = "encode";
                                                  if ((cVar5 == '\0') && (lVar11 != 0)) {
                                                    lVar14 = (**(code **)(*param_1 + 0x108))
                                                                       (param_1,lVar11,"<init>",
                                                                        &DAT_00576323);
                                                    cVar5 = (**(code **)(*param_1 + 0x720))(param_1)
                                                    ;
                                                    if ((cVar5 == '\0') && (lVar14 != 0)) {
                                                      lVar14 = (**(code **)(*param_1 + 0xe0))
                                                                         (param_1,lVar11,lVar14,
                                                                          iVar7);
                                                      cVar5 = (**(code **)(*param_1 + 0x720))
                                                                        (param_1);
                                                      if ((cVar5 == '\0') && (lVar14 != 0)) {
                                                        lVar15 = (**(code **)(*param_1 + 0x30))
                                                                           (param_1,
                                                  "android/graphics/Bitmap$CompressFormat");
                                                  cVar5 = (**(code **)(*param_1 + 0x720))(param_1);
                                                  if ((cVar5 == '\0') && (lVar15 != 0)) {
                                                    lVar16 = (**(code **)(*param_1 + 0x480))
                                                                       (param_1,lVar15,&DAT_00575f03
                                                                        ,
                                                  "Landroid/graphics/Bitmap$CompressFormat;");
                                                  cVar5 = (**(code **)(*param_1 + 0x720))(param_1);
                                                  if ((cVar5 == '\0') && (lVar16 != 0)) {
                                                    lVar15 = (**(code **)(*param_1 + 0x488))
                                                                       (param_1,lVar15,lVar16);
                                                    cVar5 = (**(code **)(*param_1 + 0x720))(param_1)
                                                    ;
                                                    if ((cVar5 == '\0') && (lVar15 != 0)) {
                                                      lVar18 = (**(code **)(*param_1 + 0x108))
                                                                         (param_1,lVar18,"compress",
                                                                                                                                                    
                                                  "(Landroid/graphics/Bitmap$CompressFormat;ILjava/io/OutputStream;)Z"
                                                  );
                                                  cVar5 = (**(code **)(*param_1 + 0x720))(param_1);
                                                  if ((cVar5 == '\0') && (lVar18 != 0)) {
                                                    cVar5 = (**(code **)(*param_1 + 0x128))
                                                                      (param_1,lVar10,lVar18,lVar15,
                                                                       0x5f,lVar14);
                                                    cVar6 = (**(code **)(*param_1 + 0x720))(param_1)
                                                    ;
                                                    if ((cVar6 == '\0') && (cVar5 != '\0')) {
                                                      lVar11 = (**(code **)(*param_1 + 0x108))
                                                                         (param_1,lVar11,
                                                                          "toByteArray",
                                                                          &DAT_005765df);
                                                      cVar5 = (**(code **)(*param_1 + 0x720))
                                                                        (param_1);
                                                      if ((cVar5 == '\0') && (lVar11 != 0)) {
                                                        lVar11 = (**(code **)(*param_1 + 0x110))
                                                                           (param_1,lVar14,lVar11);
                                                        cVar5 = (**(code **)(*param_1 + 0x720))
                                                                          (param_1);
                                                        if ((cVar5 == '\0') && (lVar11 != 0)) {
                                                          lVar18 = (**(code **)(*param_1 + 0x388))
                                                                             (param_1,param_2,
                                                                              "copyExif",
                                                                              "([B[BZIIZ)[B");
                                                          cVar5 = (**(code **)(*param_1 + 0x720))
                                                                            (param_1);
                                                          pcVar24 = "metadata";
                                                          if ((cVar5 == '\0') && (lVar18 != 0)) {
                                                            lVar11 = (**(code **)(*param_1 + 0x390))
                                                                               (param_1,param_2,
                                                                                lVar18,param_3,
                                                                                lVar11,param_5 ==
                                                                                       '\0',0,0,0);
                                                            cVar5 = (**(code **)(*param_1 + 0x720))
                                                                              (param_1);
                                                            uVar3 = local_90;
                                                            if ((cVar5 == '\0') && (lVar11 != 0)) {
                                                              uVar4 = local_90._4_4_;
                                                              puVar19 = &UNK_005764c1;
                                                              if (param_5 != '\0') {
                                                                puVar19 = &DAT_005764be;
                                                              }
                                                              dVar27 = (double)b6_now_ms();
                                                              auVar31._0_8_ = dVar27 - dVar26;
                                                              auVar31._8_8_ = 0;
                                                              __android_log_print(auVar31,5,
                                                                                  "LeicaM9M3B12",
                                                                                                                                                                    
                                                  "B8 recovery=basic_style mode=%s grade=1 guard=%d width=%u height=%u recovery_ms=%.2f vendor_model_complete=0"
                                                  ,puVar19,uVar9,uVar3 & 0xffffffff,uVar4);
                                                  bVar1 = false;
                                                  pcVar24 = "metadata";
                                                  param_3 = lVar11;
                                                  lVar11 = 0;
                                                  goto LAB_0058911c;
                                                  }
                                                  }
                                                  }
                                                  }
                                                  }
                                                  }
                                                  }
                                                  }
                                                  }
                                                  }
                                                  }
                                                  }
                                                  }
                                                  }
                                                  }
                                                  }
                                                  }
                                                  }
                                                  }
                                                  }
                                                  bVar1 = true;
                                                  lVar11 = 0;
                                                  goto LAB_0058911c;
                                                  }
                                                  }
                                                  bVar1 = true;
                                                  goto LAB_0058911c;
                                                  }
                                                  }
                                                  }
                                                  }
                                                  }
                                                  }
                                                }
                                              }
                                            }
                                          }
                                        }
                                      }
                                    }
                                  }
                                }
                              }
                            }
                          }
                          lVar10 = 0;
                          bVar1 = true;
                          lVar11 = lVar10;
                          goto LAB_0058911c;
                        }
                      }
                      lVar21 = 0;
                      lVar10 = 0;
                      bVar1 = true;
                      lVar11 = lVar21;
                      goto LAB_0058911c;
                    }
                  }
LAB_0058951c:
                  lVar21 = 0;
                  lVar20 = 0;
                  lVar10 = 0;
                  bVar1 = true;
                  lVar11 = lVar20;
                  goto LAB_0058911c;
                }
              }
            }
          }
          goto LAB_0058910c;
        }
        lVar20 = 0;
        lVar21 = 0;
        lVar12 = 0;
        lVar10 = 0;
        bVar1 = true;
        pcVar24 = "main-thread saver: no blocking recovery";
        lVar11 = 0;
      }
      else {
        lVar20 = 0;
        lVar21 = 0;
        lVar12 = 0;
        lVar10 = 0;
        bVar1 = true;
        pcVar24 = "thread check";
        lVar11 = 0;
      }
    }
    else {
      lVar20 = 0;
      lVar21 = 0;
      lVar12 = 0;
LAB_00588724:
      pcVar24 = pcVar23;
      lVar10 = 0;
      bVar1 = true;
      lVar11 = 0;
    }
  }
  else {
LAB_0058910c:
    pcVar24 = pcVar22;
    bVar1 = true;
    lVar20 = 0;
    lVar21 = 0;
    lVar12 = 0;
    lVar11 = 0;
    lVar10 = 0;
  }
LAB_0058911c:
  cVar5 = (**(code **)(*param_1 + 0x720))(param_1);
  if (cVar5 != '\0') {
    (**(code **)(*param_1 + 0x88))(param_1);
    __android_log_print(6,"LeicaM9M3B12",
                        "B8 recovery exception at %s; source retained if recovery cannot complete",
                        pcVar24);
  }
  if ((lVar11 == 0) ||
     ((lVar10 != 0 && (cVar5 = (**(code **)(*param_1 + 0xc0))(param_1,lVar10,lVar11), cVar5 != '\0')
      ))) {
LAB_0058922c:
    if (lVar21 != 0) {
LAB_00589230:
      if (lVar10 != 0) {
        lVar11 = (**(code **)(*param_1 + 0x78))(param_1);
        if (lVar11 == 0) {
          (**(code **)(*param_1 + 0x1e8))(param_1,lVar10,lVar21);
          (**(code **)(*param_1 + 0x720))(param_1);
        }
        else {
          (**(code **)(*param_1 + 0x88))(param_1);
          (**(code **)(*param_1 + 0x1e8))(param_1,lVar10,lVar21);
          (**(code **)(*param_1 + 0x720))(param_1);
          cVar5 = (**(code **)(*param_1 + 0x720))(param_1);
          if (cVar5 != '\0') {
            (**(code **)(*param_1 + 0x88))(param_1);
          }
          (**(code **)(*param_1 + 0x68))(param_1,lVar11);
          (**(code **)(*param_1 + 0xb8))(param_1,lVar11);
        }
      }
    }
  }
  else if (lVar21 != 0) {
    lVar18 = (**(code **)(*param_1 + 0x78))(param_1);
    if (lVar18 != 0) {
      (**(code **)(*param_1 + 0x88))(param_1);
      (**(code **)(*param_1 + 0x1e8))(param_1,lVar11,lVar21);
      (**(code **)(*param_1 + 0x720))(param_1);
      cVar5 = (**(code **)(*param_1 + 0x720))(param_1);
      if (cVar5 != '\0') {
        (**(code **)(*param_1 + 0x88))(param_1);
      }
      (**(code **)(*param_1 + 0x68))(param_1,lVar18);
      (**(code **)(*param_1 + 0xb8))(param_1,lVar18);
      goto LAB_0058922c;
    }
    (**(code **)(*param_1 + 0x1e8))(param_1,lVar11,lVar21);
    (**(code **)(*param_1 + 0x720))(param_1);
    if (lVar21 == 0) goto LAB_005892fc;
    goto LAB_00589230;
  }
LAB_005892fc:
  cVar5 = (**(code **)(*param_1 + 0x720))(param_1);
  if (cVar5 != '\0') {
    (**(code **)(*param_1 + 0x88))(param_1);
    __android_log_print(6,"LeicaM9M3B12",
                        "B8 recovery exception at %s; source retained if recovery cannot complete",
                        "bitmap cleanup");
  }
  if ((lVar20 != 0) && (lVar12 != 0)) {
    lVar10 = (**(code **)(*param_1 + 0x78))(param_1);
    if (lVar10 == 0) {
      (**(code **)(*param_1 + 0x1e8))(param_1,lVar12,lVar20);
      (**(code **)(*param_1 + 0x720))(param_1);
      cVar5 = (**(code **)(*param_1 + 0x720))(param_1);
      goto joined_r0x00589400;
    }
    (**(code **)(*param_1 + 0x88))(param_1);
    (**(code **)(*param_1 + 0x1e8))(param_1,lVar12,lVar20);
    (**(code **)(*param_1 + 0x720))(param_1);
    cVar5 = (**(code **)(*param_1 + 0x720))(param_1);
    if (cVar5 != '\0') {
      (**(code **)(*param_1 + 0x88))(param_1);
    }
    (**(code **)(*param_1 + 0x68))(param_1,lVar10);
    (**(code **)(*param_1 + 0xb8))(param_1,lVar10);
  }
  cVar5 = (**(code **)(*param_1 + 0x720))(param_1);
joined_r0x00589400:
  if (cVar5 != '\0') {
    (**(code **)(*param_1 + 0x88))(param_1);
    __android_log_print(6,"LeicaM9M3B12",
                        "B8 recovery exception at %s; source retained if recovery cannot complete",
                        "queue cleanup");
  }
  if (bVar1) {
    __android_log_print(6,"LeicaM9M3B12","B8 recovery=failed at=%s source_retained=1",pcVar24);
    puVar19 = &DAT_005766eb;
  }
  else {
    puVar19 = &DAT_00575fc6;
  }
  notice(param_1,puVar19);
  lVar10 = (**(code **)(*param_1 + 0xa0))(param_1,param_3);
  return lVar10;
}


