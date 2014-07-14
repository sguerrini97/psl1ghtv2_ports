
/*
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; version 2 of the License.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA
 */

#define LV1_1_IN_ARG_DECL uint64_t in_1
#define LV1_2_IN_ARG_DECL LV1_1_IN_ARG_DECL, uint64_t in_2
#define LV1_3_IN_ARG_DECL LV1_2_IN_ARG_DECL, uint64_t in_3
#define LV1_4_IN_ARG_DECL LV1_3_IN_ARG_DECL, uint64_t in_4
#define LV1_5_IN_ARG_DECL LV1_4_IN_ARG_DECL, uint64_t in_5
#define LV1_6_IN_ARG_DECL LV1_5_IN_ARG_DECL, uint64_t in_6
#define LV1_7_IN_ARG_DECL LV1_6_IN_ARG_DECL, uint64_t in_7
#define LV1_8_IN_ARG_DECL LV1_7_IN_ARG_DECL, uint64_t in_8
#define LV1_1_OUT_ARG_DECL uint64_t *out_1
#define LV1_2_OUT_ARG_DECL LV1_1_OUT_ARG_DECL, uint64_t *out_2
#define LV1_3_OUT_ARG_DECL LV1_2_OUT_ARG_DECL, uint64_t *out_3
#define LV1_4_OUT_ARG_DECL LV1_3_OUT_ARG_DECL, uint64_t *out_4
#define LV1_5_OUT_ARG_DECL LV1_4_OUT_ARG_DECL, uint64_t *out_5
#define LV1_6_OUT_ARG_DECL LV1_5_OUT_ARG_DECL, uint64_t *out_6
#define LV1_7_OUT_ARG_DECL LV1_6_OUT_ARG_DECL, uint64_t *out_7

#define LV1_0_IN_0_OUT_ARG_DECL void
#define LV1_1_IN_0_OUT_ARG_DECL LV1_1_IN_ARG_DECL
#define LV1_2_IN_0_OUT_ARG_DECL LV1_2_IN_ARG_DECL
#define LV1_3_IN_0_OUT_ARG_DECL LV1_3_IN_ARG_DECL
#define LV1_4_IN_0_OUT_ARG_DECL LV1_4_IN_ARG_DECL
#define LV1_5_IN_0_OUT_ARG_DECL LV1_5_IN_ARG_DECL
#define LV1_6_IN_0_OUT_ARG_DECL LV1_6_IN_ARG_DECL
#define LV1_7_IN_0_OUT_ARG_DECL LV1_7_IN_ARG_DECL
#define LV1_8_IN_0_OUT_ARG_DECL LV1_8_IN_ARG_DECL

#define LV1_0_IN_1_OUT_ARG_DECL                    LV1_1_OUT_ARG_DECL
#define LV1_1_IN_1_OUT_ARG_DECL LV1_1_IN_ARG_DECL, LV1_1_OUT_ARG_DECL
#define LV1_2_IN_1_OUT_ARG_DECL LV1_2_IN_ARG_DECL, LV1_1_OUT_ARG_DECL
#define LV1_3_IN_1_OUT_ARG_DECL LV1_3_IN_ARG_DECL, LV1_1_OUT_ARG_DECL
#define LV1_4_IN_1_OUT_ARG_DECL LV1_4_IN_ARG_DECL, LV1_1_OUT_ARG_DECL
#define LV1_5_IN_1_OUT_ARG_DECL LV1_5_IN_ARG_DECL, LV1_1_OUT_ARG_DECL
#define LV1_6_IN_1_OUT_ARG_DECL LV1_6_IN_ARG_DECL, LV1_1_OUT_ARG_DECL
#define LV1_7_IN_1_OUT_ARG_DECL LV1_7_IN_ARG_DECL, LV1_1_OUT_ARG_DECL
#define LV1_8_IN_1_OUT_ARG_DECL LV1_8_IN_ARG_DECL, LV1_1_OUT_ARG_DECL

#define LV1_0_IN_2_OUT_ARG_DECL                    LV1_2_OUT_ARG_DECL
#define LV1_1_IN_2_OUT_ARG_DECL LV1_1_IN_ARG_DECL, LV1_2_OUT_ARG_DECL
#define LV1_2_IN_2_OUT_ARG_DECL LV1_2_IN_ARG_DECL, LV1_2_OUT_ARG_DECL
#define LV1_3_IN_2_OUT_ARG_DECL LV1_3_IN_ARG_DECL, LV1_2_OUT_ARG_DECL
#define LV1_4_IN_2_OUT_ARG_DECL LV1_4_IN_ARG_DECL, LV1_2_OUT_ARG_DECL
#define LV1_5_IN_2_OUT_ARG_DECL LV1_5_IN_ARG_DECL, LV1_2_OUT_ARG_DECL
#define LV1_6_IN_2_OUT_ARG_DECL LV1_6_IN_ARG_DECL, LV1_2_OUT_ARG_DECL
#define LV1_7_IN_2_OUT_ARG_DECL LV1_7_IN_ARG_DECL, LV1_2_OUT_ARG_DECL

#define LV1_0_IN_3_OUT_ARG_DECL                    LV1_3_OUT_ARG_DECL
#define LV1_1_IN_3_OUT_ARG_DECL LV1_1_IN_ARG_DECL, LV1_3_OUT_ARG_DECL
#define LV1_2_IN_3_OUT_ARG_DECL LV1_2_IN_ARG_DECL, LV1_3_OUT_ARG_DECL
#define LV1_3_IN_3_OUT_ARG_DECL LV1_3_IN_ARG_DECL, LV1_3_OUT_ARG_DECL
#define LV1_4_IN_3_OUT_ARG_DECL LV1_4_IN_ARG_DECL, LV1_3_OUT_ARG_DECL
#define LV1_5_IN_3_OUT_ARG_DECL LV1_5_IN_ARG_DECL, LV1_3_OUT_ARG_DECL
#define LV1_6_IN_3_OUT_ARG_DECL LV1_6_IN_ARG_DECL, LV1_3_OUT_ARG_DECL
#define LV1_7_IN_3_OUT_ARG_DECL LV1_7_IN_ARG_DECL, LV1_3_OUT_ARG_DECL

#define LV1_0_IN_4_OUT_ARG_DECL                    LV1_4_OUT_ARG_DECL
#define LV1_1_IN_4_OUT_ARG_DECL LV1_1_IN_ARG_DECL, LV1_4_OUT_ARG_DECL
#define LV1_2_IN_4_OUT_ARG_DECL LV1_2_IN_ARG_DECL, LV1_4_OUT_ARG_DECL
#define LV1_3_IN_4_OUT_ARG_DECL LV1_3_IN_ARG_DECL, LV1_4_OUT_ARG_DECL
#define LV1_4_IN_4_OUT_ARG_DECL LV1_4_IN_ARG_DECL, LV1_4_OUT_ARG_DECL
#define LV1_5_IN_4_OUT_ARG_DECL LV1_5_IN_ARG_DECL, LV1_4_OUT_ARG_DECL
#define LV1_6_IN_4_OUT_ARG_DECL LV1_6_IN_ARG_DECL, LV1_4_OUT_ARG_DECL
#define LV1_7_IN_4_OUT_ARG_DECL LV1_7_IN_ARG_DECL, LV1_4_OUT_ARG_DECL

#define LV1_0_IN_5_OUT_ARG_DECL                    LV1_5_OUT_ARG_DECL
#define LV1_1_IN_5_OUT_ARG_DECL LV1_1_IN_ARG_DECL, LV1_5_OUT_ARG_DECL
#define LV1_2_IN_5_OUT_ARG_DECL LV1_2_IN_ARG_DECL, LV1_5_OUT_ARG_DECL
#define LV1_3_IN_5_OUT_ARG_DECL LV1_3_IN_ARG_DECL, LV1_5_OUT_ARG_DECL
#define LV1_4_IN_5_OUT_ARG_DECL LV1_4_IN_ARG_DECL, LV1_5_OUT_ARG_DECL
#define LV1_5_IN_5_OUT_ARG_DECL LV1_5_IN_ARG_DECL, LV1_5_OUT_ARG_DECL
#define LV1_6_IN_5_OUT_ARG_DECL LV1_6_IN_ARG_DECL, LV1_5_OUT_ARG_DECL
#define LV1_7_IN_5_OUT_ARG_DECL LV1_7_IN_ARG_DECL, LV1_5_OUT_ARG_DECL

#define LV1_0_IN_6_OUT_ARG_DECL                    LV1_6_OUT_ARG_DECL
#define LV1_1_IN_6_OUT_ARG_DECL LV1_1_IN_ARG_DECL, LV1_6_OUT_ARG_DECL
#define LV1_2_IN_6_OUT_ARG_DECL LV1_2_IN_ARG_DECL, LV1_6_OUT_ARG_DECL
#define LV1_3_IN_6_OUT_ARG_DECL LV1_3_IN_ARG_DECL, LV1_6_OUT_ARG_DECL
#define LV1_4_IN_6_OUT_ARG_DECL LV1_4_IN_ARG_DECL, LV1_6_OUT_ARG_DECL
#define LV1_5_IN_6_OUT_ARG_DECL LV1_5_IN_ARG_DECL, LV1_6_OUT_ARG_DECL
#define LV1_6_IN_6_OUT_ARG_DECL LV1_6_IN_ARG_DECL, LV1_6_OUT_ARG_DECL
#define LV1_7_IN_6_OUT_ARG_DECL LV1_7_IN_ARG_DECL, LV1_6_OUT_ARG_DECL

#define LV1_0_IN_7_OUT_ARG_DECL                    LV1_7_OUT_ARG_DECL
#define LV1_1_IN_7_OUT_ARG_DECL LV1_1_IN_ARG_DECL, LV1_7_OUT_ARG_DECL
#define LV1_2_IN_7_OUT_ARG_DECL LV1_2_IN_ARG_DECL, LV1_7_OUT_ARG_DECL
#define LV1_3_IN_7_OUT_ARG_DECL LV1_3_IN_ARG_DECL, LV1_7_OUT_ARG_DECL
#define LV1_4_IN_7_OUT_ARG_DECL LV1_4_IN_ARG_DECL, LV1_7_OUT_ARG_DECL
#define LV1_5_IN_7_OUT_ARG_DECL LV1_5_IN_ARG_DECL, LV1_7_OUT_ARG_DECL
#define LV1_6_IN_7_OUT_ARG_DECL LV1_6_IN_ARG_DECL, LV1_7_OUT_ARG_DECL
#define LV1_7_IN_7_OUT_ARG_DECL LV1_7_IN_ARG_DECL, LV1_7_OUT_ARG_DECL

#define LV1_1_IN_ARGS in_1
#define LV1_2_IN_ARGS LV1_1_IN_ARGS, in_2
#define LV1_3_IN_ARGS LV1_2_IN_ARGS, in_3
#define LV1_4_IN_ARGS LV1_3_IN_ARGS, in_4
#define LV1_5_IN_ARGS LV1_4_IN_ARGS, in_5
#define LV1_6_IN_ARGS LV1_5_IN_ARGS, in_6
#define LV1_7_IN_ARGS LV1_6_IN_ARGS, in_7
#define LV1_8_IN_ARGS LV1_7_IN_ARGS, in_8

#define LV1_1_OUT_ARGS out_1
#define LV1_2_OUT_ARGS LV1_1_OUT_ARGS, out_2
#define LV1_3_OUT_ARGS LV1_2_OUT_ARGS, out_3
#define LV1_4_OUT_ARGS LV1_3_OUT_ARGS, out_4
#define LV1_5_OUT_ARGS LV1_4_OUT_ARGS, out_5
#define LV1_6_OUT_ARGS LV1_5_OUT_ARGS, out_6
#define LV1_7_OUT_ARGS LV1_6_OUT_ARGS, out_7

#define LV1_0_IN_0_OUT_ARGS
#define LV1_1_IN_0_OUT_ARGS LV1_1_IN_ARGS
#define LV1_2_IN_0_OUT_ARGS LV1_2_IN_ARGS
#define LV1_3_IN_0_OUT_ARGS LV1_3_IN_ARGS
#define LV1_4_IN_0_OUT_ARGS LV1_4_IN_ARGS
#define LV1_5_IN_0_OUT_ARGS LV1_5_IN_ARGS
#define LV1_6_IN_0_OUT_ARGS LV1_6_IN_ARGS
#define LV1_7_IN_0_OUT_ARGS LV1_7_IN_ARGS

#define LV1_0_IN_1_OUT_ARGS                LV1_1_OUT_ARGS
#define LV1_1_IN_1_OUT_ARGS LV1_1_IN_ARGS, LV1_1_OUT_ARGS
#define LV1_2_IN_1_OUT_ARGS LV1_2_IN_ARGS, LV1_1_OUT_ARGS
#define LV1_3_IN_1_OUT_ARGS LV1_3_IN_ARGS, LV1_1_OUT_ARGS
#define LV1_4_IN_1_OUT_ARGS LV1_4_IN_ARGS, LV1_1_OUT_ARGS
#define LV1_5_IN_1_OUT_ARGS LV1_5_IN_ARGS, LV1_1_OUT_ARGS
#define LV1_6_IN_1_OUT_ARGS LV1_6_IN_ARGS, LV1_1_OUT_ARGS
#define LV1_7_IN_1_OUT_ARGS LV1_7_IN_ARGS, LV1_1_OUT_ARGS
#define LV1_8_IN_1_OUT_ARGS LV1_8_IN_ARGS, LV1_1_OUT_ARGS

#define LV1_0_IN_2_OUT_ARGS                LV1_2_OUT_ARGS
#define LV1_1_IN_2_OUT_ARGS LV1_1_IN_ARGS, LV1_2_OUT_ARGS
#define LV1_2_IN_2_OUT_ARGS LV1_2_IN_ARGS, LV1_2_OUT_ARGS
#define LV1_3_IN_2_OUT_ARGS LV1_3_IN_ARGS, LV1_2_OUT_ARGS
#define LV1_4_IN_2_OUT_ARGS LV1_4_IN_ARGS, LV1_2_OUT_ARGS
#define LV1_5_IN_2_OUT_ARGS LV1_5_IN_ARGS, LV1_2_OUT_ARGS
#define LV1_6_IN_2_OUT_ARGS LV1_6_IN_ARGS, LV1_2_OUT_ARGS
#define LV1_7_IN_2_OUT_ARGS LV1_7_IN_ARGS, LV1_2_OUT_ARGS

#define LV1_0_IN_3_OUT_ARGS                LV1_3_OUT_ARGS
#define LV1_1_IN_3_OUT_ARGS LV1_1_IN_ARGS, LV1_3_OUT_ARGS
#define LV1_2_IN_3_OUT_ARGS LV1_2_IN_ARGS, LV1_3_OUT_ARGS
#define LV1_3_IN_3_OUT_ARGS LV1_3_IN_ARGS, LV1_3_OUT_ARGS
#define LV1_4_IN_3_OUT_ARGS LV1_4_IN_ARGS, LV1_3_OUT_ARGS
#define LV1_5_IN_3_OUT_ARGS LV1_5_IN_ARGS, LV1_3_OUT_ARGS
#define LV1_6_IN_3_OUT_ARGS LV1_6_IN_ARGS, LV1_3_OUT_ARGS
#define LV1_7_IN_3_OUT_ARGS LV1_7_IN_ARGS, LV1_3_OUT_ARGS

#define LV1_0_IN_4_OUT_ARGS                LV1_4_OUT_ARGS
#define LV1_1_IN_4_OUT_ARGS LV1_1_IN_ARGS, LV1_4_OUT_ARGS
#define LV1_2_IN_4_OUT_ARGS LV1_2_IN_ARGS, LV1_4_OUT_ARGS
#define LV1_3_IN_4_OUT_ARGS LV1_3_IN_ARGS, LV1_4_OUT_ARGS
#define LV1_4_IN_4_OUT_ARGS LV1_4_IN_ARGS, LV1_4_OUT_ARGS
#define LV1_5_IN_4_OUT_ARGS LV1_5_IN_ARGS, LV1_4_OUT_ARGS
#define LV1_6_IN_4_OUT_ARGS LV1_6_IN_ARGS, LV1_4_OUT_ARGS
#define LV1_7_IN_4_OUT_ARGS LV1_7_IN_ARGS, LV1_4_OUT_ARGS

#define LV1_0_IN_5_OUT_ARGS                LV1_5_OUT_ARGS
#define LV1_1_IN_5_OUT_ARGS LV1_1_IN_ARGS, LV1_5_OUT_ARGS
#define LV1_2_IN_5_OUT_ARGS LV1_2_IN_ARGS, LV1_5_OUT_ARGS
#define LV1_3_IN_5_OUT_ARGS LV1_3_IN_ARGS, LV1_5_OUT_ARGS
#define LV1_4_IN_5_OUT_ARGS LV1_4_IN_ARGS, LV1_5_OUT_ARGS
#define LV1_5_IN_5_OUT_ARGS LV1_5_IN_ARGS, LV1_5_OUT_ARGS
#define LV1_6_IN_5_OUT_ARGS LV1_6_IN_ARGS, LV1_5_OUT_ARGS
#define LV1_7_IN_5_OUT_ARGS LV1_7_IN_ARGS, LV1_5_OUT_ARGS

#define LV1_0_IN_6_OUT_ARGS                LV1_6_OUT_ARGS
#define LV1_1_IN_6_OUT_ARGS LV1_1_IN_ARGS, LV1_6_OUT_ARGS
#define LV1_2_IN_6_OUT_ARGS LV1_2_IN_ARGS, LV1_6_OUT_ARGS
#define LV1_3_IN_6_OUT_ARGS LV1_3_IN_ARGS, LV1_6_OUT_ARGS
#define LV1_4_IN_6_OUT_ARGS LV1_4_IN_ARGS, LV1_6_OUT_ARGS
#define LV1_5_IN_6_OUT_ARGS LV1_5_IN_ARGS, LV1_6_OUT_ARGS
#define LV1_6_IN_6_OUT_ARGS LV1_6_IN_ARGS, LV1_6_OUT_ARGS
#define LV1_7_IN_6_OUT_ARGS LV1_7_IN_ARGS, LV1_6_OUT_ARGS

#define LV1_0_IN_7_OUT_ARGS                LV1_7_OUT_ARGS
#define LV1_1_IN_7_OUT_ARGS LV1_1_IN_ARGS, LV1_7_OUT_ARGS
#define LV1_2_IN_7_OUT_ARGS LV1_2_IN_ARGS, LV1_7_OUT_ARGS
#define LV1_3_IN_7_OUT_ARGS LV1_3_IN_ARGS, LV1_7_OUT_ARGS
#define LV1_4_IN_7_OUT_ARGS LV1_4_IN_ARGS, LV1_7_OUT_ARGS
#define LV1_5_IN_7_OUT_ARGS LV1_5_IN_ARGS, LV1_7_OUT_ARGS
#define LV1_6_IN_7_OUT_ARGS LV1_6_IN_ARGS, LV1_7_OUT_ARGS
#define LV1_7_IN_7_OUT_ARGS LV1_7_IN_ARGS, LV1_7_OUT_ARGS

#if !defined(LV1_HVCALL)
#define LV1_HVCALL(name, in, out, num)	extern int64_t lv1_##name(LV1_##in##_IN_##out##_OUT_ARG_DECL);
#endif

LV1_HVCALL(allocate_memory,                               4, 2,   0 )
LV1_HVCALL(write_htab_entry,                              4, 0,   1 )
LV1_HVCALL(construct_virtual_address_space,               3, 2,   2 )
LV1_HVCALL(invalidate_htab_entries,                       5, 0,   3 )
LV1_HVCALL(get_virtual_address_space_id_of_ppe,           1, 1,   4 )
LV1_HVCALL(query_logical_partition_address_region_info,   1, 5,   6 )
LV1_HVCALL(select_virtual_address_space,                  1, 0,   7 )
LV1_HVCALL(pause,                                         1, 0,   9 )
LV1_HVCALL(destruct_virtual_address_space,                1, 0,  10 )
LV1_HVCALL(configure_irq_state_bitmap,                    3, 0,  11 )
LV1_HVCALL(connect_irq_plug_ext,                          5, 0,  12 )
LV1_HVCALL(release_memory,                                1, 0,  13 )
LV1_HVCALL(put_iopte,                                     5, 0,  15 )
LV1_HVCALL(disconnect_irq_plug_ext,                       3, 0,  17 )
LV1_HVCALL(construct_event_receive_port,                  0, 1,  18 )
LV1_HVCALL(destruct_event_receive_port,                   1, 0,  19 )
LV1_HVCALL(send_event_locally,                            1, 0,  24 )
LV1_HVCALL(end_of_interrupt,                              1, 0,  27 )
LV1_HVCALL(connect_irq_plug,                              2, 0,  28 )
LV1_HVCALL(disconnect_irq_plug,                           1, 0,  29 )
LV1_HVCALL(end_of_interrupt_ext,                          3, 0,  30 )
LV1_HVCALL(did_update_interrupt_mask,                     2, 0,  31 )
LV1_HVCALL(shutdown_logical_partition,                    1, 0,  44 )
LV1_HVCALL(destruct_logical_spe,                          1, 0,  54 )
LV1_HVCALL(construct_logical_spe,                         7, 6,  57 )
LV1_HVCALL(set_spe_interrupt_mask,                        3, 0,  61 )
LV1_HVCALL(set_spe_transition_notifier,                   3, 0,  64 )
LV1_HVCALL(disable_logical_spe,                           2, 0,  65 )
LV1_HVCALL(clear_spe_interrupt_status,                    4, 0,  66 )
LV1_HVCALL(get_spe_interrupt_status,                      2, 1,  67 )
LV1_HVCALL(get_logical_ppe_id,                            0, 1,  69 )
LV1_HVCALL(set_interrupt_mask,                            5, 0,  73 )
LV1_HVCALL(get_logical_partition_id,                      0, 1,  74 )
LV1_HVCALL(configure_execution_time_variable,             1, 0,  77 )
LV1_HVCALL(get_spe_irq_outlet,                            2, 1,  78 )
LV1_HVCALL(set_spe_privilege_state_area_1_register,       3, 0,  79 )
LV1_HVCALL(create_repository_node,                        6, 0,  90 )
LV1_HVCALL(get_repository_node_value,                     5, 2,  91 )
LV1_HVCALL(modify_repository_node_value,                  6, 0,  92 )
LV1_HVCALL(remove_repository_node,                        4, 0,  93 )
LV1_HVCALL(read_htab_entries,                             2, 5,  95 )
LV1_HVCALL(set_dabr,                                      2, 0,  96 )
LV1_HVCALL(get_total_execution_time,                      2, 1, 103 )
LV1_HVCALL(allocate_io_segment,                           3, 1, 116 )
LV1_HVCALL(release_io_segment,                            2, 0, 117 )
LV1_HVCALL(construct_io_irq_outlet,                       1, 1, 120 )
LV1_HVCALL(destruct_io_irq_outlet,                        1, 0, 121 )
LV1_HVCALL(map_htab,                                      1, 1, 122 )
LV1_HVCALL(unmap_htab,                                    1, 0, 123 )
LV1_HVCALL(get_version_info,                              0, 1, 127 )
LV1_HVCALL(insert_htab_entry,                             6, 3, 158 )
LV1_HVCALL(read_virtual_uart,                             3, 1, 162 )
LV1_HVCALL(write_virtual_uart,                            3, 1, 163 )
LV1_HVCALL(set_virtual_uart_param,                        3, 0, 164 )
LV1_HVCALL(get_virtual_uart_param,                        2, 1, 165 )
LV1_HVCALL(configure_virtual_uart_irq,                    1, 1, 166 )
LV1_HVCALL(open_device,                                   3, 0, 170 )
LV1_HVCALL(close_device,                                  2, 0, 171 )
LV1_HVCALL(map_device_mmio_region,                        5, 1, 172 )
LV1_HVCALL(unmap_device_mmio_region,                      3, 0, 173 )
LV1_HVCALL(allocate_device_dma_region,                    5, 1, 174 )
LV1_HVCALL(free_device_dma_region,                        3, 0, 175 )
LV1_HVCALL(map_device_dma_region,                         6, 0, 176 )
LV1_HVCALL(unmap_device_dma_region,                       4, 0, 177 )
LV1_HVCALL(net_add_multicast_address,                     4, 0, 185 )
LV1_HVCALL(net_remove_multicast_address,                  4, 0, 186 )
LV1_HVCALL(net_start_tx_dma,                              4, 0, 187 )
LV1_HVCALL(net_stop_tx_dma,                               3, 0, 188 )
LV1_HVCALL(net_start_rx_dma,                              4, 0, 189 )
LV1_HVCALL(net_stop_rx_dma,                               3, 0, 190 )
LV1_HVCALL(net_set_interrupt_status_indicator,            4, 0, 191 )
LV1_HVCALL(net_set_interrupt_mask,                        4, 0, 193 )
LV1_HVCALL(net_control,                                   6, 2, 194 )
LV1_HVCALL(connect_interrupt_event_receive_port,          4, 0, 197 )
LV1_HVCALL(disconnect_interrupt_event_receive_port,       4, 0, 198 )
LV1_HVCALL(get_spe_all_interrupt_statuses,                1, 1, 199 )
LV1_HVCALL(deconfigure_virtual_uart_irq,                  0, 0, 202 )
LV1_HVCALL(enable_logical_spe,                            2, 0, 207 )
LV1_HVCALL(gpu_open,                                      1, 0, 210 )
LV1_HVCALL(gpu_close,                                     0, 0, 211 )
LV1_HVCALL(gpu_device_map,                                1, 2, 212 )
LV1_HVCALL(gpu_device_unmap,                              1, 0, 213 )
LV1_HVCALL(gpu_memory_allocate,                           5, 2, 214 )
LV1_HVCALL(gpu_memory_free,                               1, 0, 216 )
LV1_HVCALL(gpu_context_allocate,                          2, 5, 217 )
LV1_HVCALL(gpu_context_free,                              1, 0, 218 )
LV1_HVCALL(gpu_context_iomap,                             5, 0, 221 )
LV1_HVCALL(gpu_context_attribute,                         6, 0, 225 )
LV1_HVCALL(gpu_context_intr,                              1, 1, 227 )
LV1_HVCALL(gpu_attribute,                                 5, 0, 228 )
LV1_HVCALL(get_rtc,                                       0, 2, 232 )
LV1_HVCALL(set_ppe_periodic_tracer_frequency,             1, 0, 240 )
LV1_HVCALL(start_ppe_periodic_tracer,                     5, 0, 241 )
LV1_HVCALL(stop_ppe_periodic_tracer,                      1, 1, 242 )
LV1_HVCALL(storage_read,                                  6, 1, 245 )
LV1_HVCALL(storage_write,                                 6, 1, 246 )
LV1_HVCALL(storage_send_device_command,                   6, 1, 248 )
LV1_HVCALL(storage_get_async_status,                      1, 2, 249 )
LV1_HVCALL(storage_check_async_status,                    2, 1, 254 )
LV1_HVCALL(panic,                                         1, 0, 255 )
LV1_HVCALL(construct_lpm,                                 6, 3, 140 )
LV1_HVCALL(destruct_lpm,                                  1, 0, 141 )
LV1_HVCALL(start_lpm,                                     1, 0, 142 )
LV1_HVCALL(stop_lpm,                                      1, 1, 143 )
LV1_HVCALL(copy_lpm_trace_buffer,                         3, 1, 144 )
LV1_HVCALL(add_lpm_event_bookmark,                        5, 0, 145 )
LV1_HVCALL(delete_lpm_event_bookmark,                     3, 0, 146 )
LV1_HVCALL(set_lpm_interrupt_mask,                        3, 1, 147 )
LV1_HVCALL(get_lpm_interrupt_status,                      1, 1, 148 )
LV1_HVCALL(set_lpm_general_control,                       5, 2, 149 )
LV1_HVCALL(set_lpm_interval,                              3, 1, 150 )
LV1_HVCALL(set_lpm_trigger_control,                       3, 1, 151 )
LV1_HVCALL(set_lpm_counter_control,                       4, 1, 152 )
LV1_HVCALL(set_lpm_group_control,                         3, 1, 153 )
LV1_HVCALL(set_lpm_debug_bus_control,                     3, 1, 154 )
LV1_HVCALL(set_lpm_counter,                               5, 2, 155 )
LV1_HVCALL(set_lpm_signal,                                7, 0, 156 )
LV1_HVCALL(set_lpm_spr_trigger,                           2, 0, 157 )
LV1_HVCALL(undocumented_function_114,                     3, 1, 114 )
LV1_HVCALL(undocumented_function_115,                     1, 0, 115 )
LV1_HVCALL(undocumented_function_138,			  2, 0, 138 )
LV1_HVCALL(undocumented_function_99, 			  2, 0, 99  )
LV1_HVCALL(undocumented_function_62, 			  5, 0, 62  )
LV1_HVCALL(undocumented_function_167, 			  2, 1, 167 )
LV1_HVCALL(undocumented_function_168,			  3, 0, 168 )

