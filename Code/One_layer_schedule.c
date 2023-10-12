primfn(DRAM_1_3: handle, DRAM_1_4: handle, DRAM_1_5: handle) -> ()
  attr = {"from_legacy_te_schedule": True, "global_symbol": "TVM-Mod", "tir.noalias": True}
  buffers = {DRAM_1_2: Buffer(DRAM_1_6: Pointer(int16), int16, [64896], []),
             DRAM_1_1: Buffer(DRAM_1_7: Pointer(int16), int16, [884736], []),
             DRAM_1: Buffer(DRAM_1_8: Pointer(int16), int16, [57600], [])}
  buffer_map = {DRAM_1_3: DRAM_1, DRAM_1_4: DRAM_1_1, DRAM_1_5: DRAM_1_2} {
  allocate(Filter_Buffer_1: Pointer(local int16), int16, [3456]), storage_scope = local;
  allocate(Input_Buffer_1: Pointer(local int16), int16, [57600]), storage_scope = local;
  allocate(Filter_RF_1: Pointer(wmma.matrix_b int16), int16, [884736]), storage_scope = wmma.matrix_b;
  allocate(Input_RF_1: Pointer(wmma.matrix_a int16), int16, [43264]), storage_scope = wmma.matrix_a;
  allocate(Output_RF_1: Pointer(wmma.accumulator int16), int16, [64896]), storage_scope = wmma.accumulator;
  allocate(Output_Buffer_1: Pointer(local int16), int16, [64896]), storage_scope = local {
    for (i0: int32, 0, 384) {
      attr [IterVar(i1: int32, (nullptr), "DataPar", "")] "pragma_dma_copy" = "Filter_DMA_1";
      for (i1, 0, 3) {
        for (i2: int32, 0, 3) {
          Filter_Buffer_1_1: Buffer(Filter_Buffer_1, int16, [3456], [], scope="local")[(((i0*9) + (i1*3)) + i2)] = DRAM_1_1[((((i0*2304) + (i1*768)) + (i2*256)) + input_c: int32)]
        }
      }
    }
    for (i3: int32, 0, 256) {
      attr [IterVar(i1_1: int32, (nullptr), "DataPar", "")] "pragma_dma_copy" = "Input_DMA_1";
      for (i1_1, 0, 15) {
        for (i2_1: int32, 0, 15) {
          Input_Buffer_1_1: Buffer(Input_Buffer_1, int16, [57600], [], scope="local")[(((i1_1*3840) + (i2_1*256)) + i3)] = DRAM_1[(((i1_1*3840) + (i2_1*256)) + i3)]
        }
      }
    }
    attr [IterVar(i0_1: int32, (nullptr), "DataPar", "")] "pragma_Parallel" = 1 {
      for (kkw: int32, 0, 3) {
        for (kkh: int32, 0, 3) {
          for (kinput_c: int32, 0, 256) {
            for (output_c: int32, 0, 384) {
              attr [IterVar(output_h: int32, (nullptr), "DataPar", "")] "pragma_noc_copy" = "Filter_NoC_1";
              attr [IterVar(output_h, (nullptr), "DataPar", "")] "pragma_unroll_NoC" = 1;
              for (output_h, 0, 3) {
                attr [IterVar(output_w: int32, (nullptr), "DataPar", "")] "pragma_unroll_NoC" = 1;
                for (output_w, 0, 3) {
                  Filter_RF_1_1: Buffer(Filter_RF_1, int16, [884736], [], scope="wmma.matrix_b")[((((output_c*2304) + (output_h*768)) + (output_w*256)) + kinput_c)] = Filter_Buffer_1_1[(((output_c*9) + (kkh*3)) + kkw)]
                }
              }
            }
          }
        }
      }
      for (ikw: int32, 0, 3) {
        for (ikh: int32, 0, 3) {
          for (input_c_1: int32, 0, 256) {
            for (ioutput_c: int32, 0, 384) {
              attr [IterVar(output_h_1: int32, (nullptr), "DataPar", "")] "pragma_noc_copy" = "Input_NoC_1";
              attr [IterVar(output_h_1, (nullptr), "DataPar", "")] "pragma_unroll_NoC" = 1;
              for (output_h_1, 0, 13) {
                attr [IterVar(output_w_1: int32, (nullptr), "DataPar", "")] "pragma_unroll_NoC" = 1;
                for (output_w_1, 0, 13) {
                  Input_RF_1_1: Buffer(Input_RF_1, int16, [43264], [], scope="wmma.matrix_a")[(((output_h_1*3328) + (output_w_1*256)) + input_c_1)] = Input_Buffer_1_1[(((((output_h_1*3840) + (ikh*3840)) + (output_w_1*256)) + (ikw*256)) + input_c_1)]
                }
              }
            }
          }
        }
      }
      for (output_h_2: int32, 0, 13) {
        for (kh: int32, 0, 3) {
          for (output_c_1: int32, 0, 384) {
            for (input_c_2: int32, 0, 256) {
              attr [IterVar(output_w_2: int32, (nullptr), "DataPar", "")] "pragma_mac_compute" = "{'value': 'SystolicArray_1', 'unit': 'PE_1', 'stride': [1, 1], 'padding': (1, 1), 'pooling': '', 'pooling_window': (1, 1)}";
              for (output_w_2, 0, 13) {
                for (kw: int32, 0, 3) {
                  Output_RF_1_1: Buffer(Output_RF_1, int16, [64896], [], scope="wmma.accumulator")[(((output_h_2*4992) + (output_w_2*384)) + output_c_1)] = (Output_RF_1_1[(((output_h_2*4992) + (output_w_2*384)) + output_c_1)] + (Filter_RF_1_1[((((output_c_1*2304) + (kh*768)) + (kw*256)) + input_c_2)]*Input_RF_1_1[(((((output_h_2*3328) + (kh*3328)) + (output_w_2*256)) + (kw*256)) + input_c_2)]))
                }
              }
            }
          }
        }
      }
      for (kw_1: int32, 0, 3) {
        for (kh_1: int32, 0, 3) {
          for (input_c_3: int32, 0, 256) {
            for (output_c_2: int32, 0, 384) {
              attr [IterVar(output_h_3: int32, (nullptr), "DataPar", "")] "pragma_noc_copy" = "Output_NoC_1";
              attr [IterVar(output_h_3, (nullptr), "DataPar", "")] "pragma_unroll_NoC" = 1;
              for (output_h_3, 0, 13) {
                attr [IterVar(output_w_3: int32, (nullptr), "DataPar", "")] "pragma_unroll_NoC" = 1;
                for (output_w_3, 0, 13) {
                  Output_Buffer_1_1: Buffer(Output_Buffer_1, int16, [64896], [], scope="local")[(((output_h_3*4992) + (output_w_3*384)) + output_c_2)] = Output_RF_1_1[(((output_h_3*4992) + (output_w_3*384)) + output_c_2)]
                }
              }
            }
          }
        }
      }
      for (i3_1: int32, 0, 384) {
        attr [IterVar(i2_2: int32, (nullptr), "DataPar", "")] "pragma_dma_copy" = "Output_DMA_1";
        for (i2_2, 0, 13) {
          for (i1_2: int32, 0, 13) {
            DRAM_1_2[(((i1_2*4992) + (i2_2*384)) + i3_1)] = Output_Buffer_1_1[(((i1_2*4992) + (i2_2*384)) + i3_1)]
          }
        }
      }
    }
  }
}
