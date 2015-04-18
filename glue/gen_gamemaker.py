# Gamemaker wrapper generator

import soloud_codegen 

UNSUPPORTED_TYPES = {
    "int":0,
    "void":0,
    "const char *":0,
    "unsigned int":0,
    "float":0,
    "double":0,
    "float *":1,
    "unsigned char *":1
}

for soloud_type in soloud_codegen.soloud_type:
    UNSUPPORTED_TYPES[soloud_type + " *"] = 0

restart = 1
while restart == 1:
  restart = 0
  idx = 0
  for x in soloud_codegen.soloud_func:
    if restart == 0:
        delx = 0
        if UNSUPPORTED_TYPES[x[0]] == 1:
          delx = 1
        for p in x[2]:
          if len(p) > 0:
              if UNSUPPORTED_TYPES[p[0]] == 1:
                  delx = 1
        if delx == 1:
          print "removing " + soloud_codegen.soloud_func[idx][1] + " (unsupported variable type)"
          del soloud_codegen.soloud_func[idx]
          restart = 1
        else:
          idx = idx + 1

fo = open("soloud.extension.gmx", "w")

# type 1 = string, type 2 = double. 

PTRTYPE = "2"

C_TO_GMX_TYPES = {
    "int":"2",
    "void":"2",
    "const char *":PTRTYPE,
    "unsigned int":"2",
    "float":"2",
    "double":"2",
    "float *":PTRTYPE,
    "unsigned char *":PTRTYPE
}

for soloud_type in soloud_codegen.soloud_type:
    C_TO_GMX_TYPES[soloud_type + " *"] = PTRTYPE



fo.write("""<!--SoLoud wrapper (extension) for game maker-->
<!--This Document is generated by gen_gamemaker.py, if you edit it by hand then you do so at your own risk!-->
<extension>
  <name>soloud</name>
  <version>1.0.0</version>
  <packageID></packageID>
  <ProductID>ACBD3CFF4E539AD869A0E8E3B4B022DD</ProductID>
  <date>17/04/15</date>
  <license>Free to use, also for commercial games.</license>
  <description></description>
  <helpfile></helpfile>
  <androidProps>0</androidProps>
  <iosProps>0</iosProps>
  <installdir></installdir>
  <classname></classname>
  <androidclassname></androidclassname>
  <sourcedir></sourcedir>
  <androidsourcedir></androidsourcedir>
  <macsourcedir></macsourcedir>
  <maclinkerflags></maclinkerflags>
  <androidinject></androidinject>
  <iosSystemFrameworks/>
  <iosThirdPartyFrameworks/>
  <androidPermissions/>
  <IncludedResources/>
  <files>
    <file>
      <filename>soloud_gamemaker_dll.dll</filename>
      <origname>extensions\soloud_gamemaker_dll.dll</origname>
      <init></init>
      <final></final>
      <kind>1</kind>
      <uncompress>0</uncompress>
      <ConfigOptions>
        <Config name="Default">
          <CopyToMask>542113856</CopyToMask>
        </Config>
      </ConfigOptions>
      <ProxyFiles>
        <ProxyFile>
          <Name>soloud_x86.dll</Name>
          <TargetMask>1048640</TargetMask>
        </ProxyFile>
        <ProxyFile>
          <Name>msvcr100.dll</Name>
          <TargetMask>1048640</TargetMask>
        </ProxyFile>
        <ProxyFile>
          <Name>soloud_gamemaker_dll.dll</Name>
          <TargetMask>1048640</TargetMask>
        </ProxyFile>
      </ProxyFiles>
      <functions>
""")

for x in soloud_codegen.soloud_func:
  fo.write("        <function>\n")
  fo.write("          <name>" + x[1] + "</name>\n")
  fo.write("          <externalName>" + x[1] + "</externalName>\n")
  fo.write("          <kind>11</kind>\n")
  fo.write("          <help>Original function: ")
  fo.write(x[0] + " " + x[1] + "(")
  first = 1
  for p in x[2]:
    if len(p) > 0:
      if first == 0:
        fo.write(", ")
      else:
        first = 0
      fo.write(p[0] + " " + p[1])
  fo.write(")</help>\n")
  fo.write("          <returnType>" + C_TO_GMX_TYPES[x[0]] + "</returnType>\n")
  argcount = 0
  for p in x[2]:
    if len(p) > 0:
      argcount = argcount + 1
  
  fo.write("          <argCount>" + str(argcount) + "</argCount>\n")
  fo.write("          <args>\n")
  for p in x[2]:
    if len(p) > 0:
      fo.write("            <arg>" + C_TO_GMX_TYPES[p[0]] + "</arg>\n")    
  fo.write("          </args>\n")
  fo.write("        </function>\n")

fo.write("""      </functions>
      <constants>
""")
      
for x in soloud_codegen.soloud_enum:
   fo.write("        <constant>\n")
   fo.write("          <name>" + x + "</name>\n")
   fo.write("          <value>" + str(soloud_codegen.soloud_enum[x]) + "</value>\n")
   fo.write("          <hidden>0</hidden>\n")
   fo.write("        </constant>\n")
fo.write("""      </constants>
    </file>
  </files>
</extension>
""")
  
fo.close()
print "soloud.extension.gmx generated"


fo = open("soloud_gamemaker_dll.c", "w")
fo.write("""/* SoLoud-gamemaker wrapper dll. Generated by gen_gamemaker-py */
#include <windows.h>
#include <stdio.h>
#include <stdlib.h>

// Not exactly fast, but should do it for now..
struct PtrStore
{
    double key;
    void * val;
};

#define MAXSTORE 2048
static int gMaxStore = 0;
static struct PtrStore gStore[MAXSTORE];

static void* doubleToPointer(double d)
{
    int i;
    if (d == 0)
        return 0;
    for (i = 0; i < gMaxStore; i++)
        if (gStore[i].key == d)
            return gStore[i].val;
    return 0;
}

static double pointerToDouble(void *p)
{
    double key = gMaxStore+1;
    if (p == 0)
        return 0;
    if (gMaxStore == MAXSTORE)
        return 0;
    gStore[gMaxStore].val = p;
    gStore[gMaxStore].key = key;
    gMaxStore++;
    return key;
}

static HMODULE openDll()
{
    HMODULE res;
	res = LoadLibraryA("soloud_x86.dll");
    return res;
}

static void* getDllProc(HMODULE aDllHandle, const char *aProcName)
{
    return GetProcAddress(aDllHandle, aProcName);
}

static HMODULE dll = NULL;

static void* getSoloudProc(const char *aProcName)
{
    void *ret;
    if (!dll)
        dll = openDll();
    if (!dll)
        return 0;
    ret = getDllProc(dll, aProcName);
    return ret;
}

""")

MASK_TYPES = {
    "int":"int",
    "void":"void",
    "const char *":"const char *",
    "unsigned int":"unsigned int",
    "float":"float",
    "double":"double",
    "float *":"float *",
    "unsigned char *":"usigned char *"
}

for soloud_type in soloud_codegen.soloud_type:
    MASK_TYPES[soloud_type + " *"] = "void *"

for x in soloud_codegen.soloud_func:
  fo.write("typedef " + MASK_TYPES[x[0]] + " (*dllproc_" + x[1] + ")(")
  first = 1
  for p in x[2]:
    if len(p) > 0:
      if first == 0:
        fo.write(", ")
      else:
        first = 0
      fo.write(MASK_TYPES[p[0]] + " " + p[1])
  fo.write(");\n")

fo.write("\n")

for x in soloud_codegen.soloud_func:
  fo.write("dllproc_" + x[1] + " p_" + x[1] + " = NULL;\n")

fo.write("\n")

C_TO_GMX_DLL_TYPES = {
    "int":"double",
    "void":"double",
    "const char *":"char *",
    "unsigned int":"double",
    "float":"double",
    "double":"double",
    "float *":"char *",
    "unsigned char *":"char *"
}

for soloud_type in soloud_codegen.soloud_type:
    C_TO_GMX_DLL_TYPES[soloud_type + " *"] = "double"

IS_HANDLE_TYPE = {
    "int":0,
    "void":0,
    "const char *":0,
    "unsigned int":0,
    "float":0,
    "double":0,
    "float *":0,
    "unsigned char *":0
}
for soloud_type in soloud_codegen.soloud_type:
    IS_HANDLE_TYPE[soloud_type + " *"] = 1


for x in soloud_codegen.soloud_func:
  fo.write(C_TO_GMX_DLL_TYPES[x[0]] + " " + x[1] + "(")
  first = 1
  for p in x[2]:
    if len(p) > 0:
      if first == 0:
        fo.write(", ")
      else:
        first = 0
      fo.write(C_TO_GMX_DLL_TYPES[p[0]] + " " + p[1])
  fo.write(")\n")
  fo.write("{\n")
  fo.write("    if (p_" + x[1] + " == NULL)\n")
  fo.write("        p_" + x[1] + " = getSoloudProc(\"" + x[1] + "\");\n")
  fo.write("    if (p_" + x[1] + " == NULL)\n")
  if (x[0] == "void"):
    fo.write("        return 0;\n")
  else:
    fo.write("        return (" + C_TO_GMX_DLL_TYPES[x[0]] + ")0;\n")
  if (x[0] == "void"):
    fo.write("    p_" + x[1] + "(")
  else:
    if IS_HANDLE_TYPE[x[0]]:
        fo.write("    return ("+ C_TO_GMX_DLL_TYPES[x[0]] + ")pointerToDouble(p_" + x[1] + "(")
    else:
        fo.write("    return ("+ C_TO_GMX_DLL_TYPES[x[0]] + ")p_" + x[1] + "(")
  first = 1
  for p in x[2]:
    if len(p) > 0:
      if first == 0:
        fo.write(", ")
      else:
        first = 0
      if IS_HANDLE_TYPE[p[0]] == 1:
        fo.write("(" + MASK_TYPES[p[0]] + ")doubleToPointer(" + p[1] + ")")
      else:
        fo.write("(" + MASK_TYPES[p[0]] + ")" + p[1])
  if IS_HANDLE_TYPE[x[0]]:
    fo.write("));\n")
  else:
    fo.write(");\n")
  if (x[0] == "void"):
    fo.write("  return 0;\n")
  fo.write("}\n")
  fo.write("\n")      

fo.close()
print "soloud_gamemaker_dll.c generated"

fo = open("soloud_gamemaker_dll.def", "w")
fo.write("EXPORTS\n")
for x in soloud_codegen.soloud_func:
  fo.write("\t" + x[1] + "\n")
fo.close()
print "soloud_gamemaker_dll.def generated"
