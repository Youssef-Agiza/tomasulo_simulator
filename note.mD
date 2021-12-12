# Soreboard and Processor Stages

- **Issue:**

  - Instruction can be issued only if:
    - there is a free functional unit
    - there is no WAW hazard. The functional unit is reserved (marked as busy)
  - Issuing is done in order.

- **Dispatch:**
  - instructions are dispatched if:
    - the operands are ready (preventing RAW).
- **Execute:** No conditions but notifies the scoreboard when done.
- **Write Result:** If result ready and no WAR hazards.

- For **Functinal Units:** free/busy flag $U_a$
- For **instructions**
  - $F_j$ and $F_k$ are source registers. $F_i$ is destination register.
  - **$Q_j,Q_k$:** Units producing operands $j,k$.
- For **Result Register:** $P_i$ is result produced by unit $i$

## Algorithm

- **Issue:**

  - **Condition:** If $U_a=0$ (Unit a is free) and $P_i=0$ (no WAW).
  - **Step:**
    - $U_a=1$; Record $F_i,F_j,F_k$
    - Record $Q_j,Q_k$ and $R_j,R_k$
    - Record $P_i=U_a$

- **Dispatch:**

  - **Condition:** $R_j=1$ and $R_k=1$ ( source register are ready:)
  - **Step:** send $F_j$ and $F_k$ to unit _a_.

- **Execute:** when done, ask for permission to write.
- **Write Result:**
  - **Condition:** if there is an instruction before this that was issues but not dispatched whose $Q_j=a$ or $Q_k=a$, stall
  - **Step:** $U_a=0$ and $P_i=0$

---

**Register Renaming:** Used to avoid WAR and WAW.

**Reservation Stations:** Used for instructions leaving the
front-end without being ready to execute yet (due to RAW or
structural hazards)

**Reorder Buffer:** Used to preserve program semantics.

---

# Renaming Registers

- We use **logical** or **architectural** registers to rename the register we have, and in turn, avoid the **WAW** and **WAR** hazards.

**Renaming Stage.** $Inst_m: R_i \leftarrow R_j$ op $R_k$ becomes $R_a \leftarrow R_b$ op $R_c$, where

$R_b=Rename(R_j);$\
$R_c=Rename(R_k);$\
$R_a=freelist(first);$\
$Rename(R_i)=freelist(first);$\
$first\leftarrow next(first);$

- Rename(R) is the current mapping function.
- freelist is a list of physical registers not used yet.
- first is a pointer pointing to the next one available.

# Reservation Stations

Buffers used to:

- store the values of the operands that are ready and the units producing those who are not.
- **keep track** of operation readiness.
-

# To do

- [ ] Instruction should keep track of cycles in which it was issued, executed(start and end), and written back
- [ ]  find a way to broadcast the write back to other rs
- [ ]  parsing the remaining instructions
- [ ]  reading and writing from and to the memory
- [ ]  