def generate_nvic_ipr_macros(num_ipr_registers):
    code_output = ""
    for i in range(num_ipr_registers):
        code_output += f"/* NVIC IPR{i} register as macros */\n\n"
        for j in range(4):
            interrupt_num = (i * 4) + j
            shift_amount = j * 8
            code_output += f"#define NVIC_IPR{i}_PRI_{interrupt_num}(v) ( ( (v) & 0xFF ) << {shift_amount} )\n"
            code_output += f"#define NVIC_IPR{i}_PRI_{interrupt_num}_MASK NVIC_IPR{i}_PRI_{interrupt_num}(ALL1)\n"
        code_output += "\n"
    return code_output

full_ipr_macros = generate_nvic_ipr_macros(60)

with open("auto.txt", "w") as file:
    file.write(full_ipr_macros)
    file.close()
