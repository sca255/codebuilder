#include <QtCore/QCoreApplication>
#include <QtCore>
#include <string_view>

int main(int argc, char* argv[])
{
    QCoreApplication a(argc, argv);
    QFile file(argv[2]);
    QTextStream stream(stdout);
    stream << "File: " << argv[2] << "\n";
    stream.flush();
    file.setPermissions(QFileDevice::WriteUser);
    file.open(QIODevice::ReadOnly);
    QFile optfl(argv[3]);
    optfl.open(QIODevice::WriteOnly);
    optfl.setPermissions(QFileDevice::WriteUser);
    QString optdata="";

    QString arg1 = QString(argv[1]);
    //stream << "s"<<argv[1]<<"e";
    //stream << (arg1 == "-py ");
    //stream << (arg1 == "-py");
    stream.flush();
    
    if (arg1 == "-py"){
        while (true) {
            QString str = QString(file.readLine(1024));
            //stream << str;;
            str = str.trimmed();
            stream.flush();
            QStringList list = str.split(" ");
            if (list[0]=="end"){
                break;
            }
            if (list[0] == "strcls") {
                optdata=optdata.append("class " + list[1] + ":\n");
            }
            else if (list[0] == "strdef") {
				optdata=optdata.append("    def " + list[1] + ":\n");
			}
            else if (list[0] == "strret") {
				optdata=optdata.append("        return " + list[1] + "\n");
			}
            else if (list[0] == "strmetif") {
				optdata=optdata.append("    if " + list[1] + ":\n");
			}
            else if (list[0] == "strmetelse") {
				optdata=optdata.append("    else:\n");
			}
            else if (list[0] == "strmetwh") {
				optdata=optdata.append("    while " + list[1] + ":\n");
			}
            else if (list[0] == "strmetinfor") {
				optdata=optdata.append("    for " + list[1] + " in " + list[2] + ":\n");
			}
            else if (list[0] == "strclsdef") {
				optdata=optdata.append("    def " + list[1] + "(self):\n");
			}
            else if (list[0] == "strif") {
				optdata=optdata.append("if " + list[1] + ":\n");
			}
            else if (list[0] == "strelse") {
				optdata=optdata.append("else:\n");
			}
            else if (list[0] == "strwh") {
				optdata=optdata.append("while " + list[1] + ":\n");
			}
            else if (list[0] == "strinfor") {
				optdata=optdata.append("for " + list[1] + " in " + list[2] + ":\n");
			}
            else if (list[0] == "str__init__") {
				optdata=optdata.append("    def __init__(self):\n");
			}
            else if (list[0] == "strfor"){
                optdata=optdata.append("for():");
            }
            else if (list[0] == "imp") {
                optdata=optdata.append("import " + list[1] + "\n");
            }stream << file.error();
            stream << optfl.error();
            stream << file.errorString();
            stream << optfl.errorString();
            //stream << "//error below if found";
            stream.flush();
        }
    }
    else if (arg1 == "-cpp") {
        optdata = optdata.append("#include <iostream>\n#include <string>\n");
        while (true) {
			QString str = QString(file.readLine(1024));
			str = str.trimmed();
			QStringList list = str.split(" ");
            if (list[0] == "end") {
				break;
			}
            if (list[0] == "strcls") {
                if (list[2] == "n")
                    optdata = optdata.append("class " + list[1] + " {\npublic:\n\t\nprivate:\n\t\nprotected:\n\t\n}");
                else if (list[2] == "c")
                    optdata = optdata.append("class " + list[1] + " {\npublic:\n\t" + list[1] + "()\n\t\nprivate:\n\t\nprotected:\n\t\n}");
                else if (list[2] == "d")
                    optdata = optdata.append("class " + list[1] + " {\npublic:\n\t~" + list[1] + "()\n\t\nprivate:\n\t\nprotected:\n\t\n}");
                else if (list[2] == "cd")
                    optdata = optdata.append("class " + list[1] + " {\npublic:\n\t" + list[1] + "()\n\t~" + list[1] + "()\n\t\nprivate:\n\t\nprotected:\n\t\n}");
            }
            else if (list[0] == "strfunc") {
                if (list[2] == "int") {
                    if (list[4] == "n") {
                        if (list[3] == "n")
                            optdata = optdata.append("int " + list[1] + "(){\n");
                        else if (list[3] == "16")
                            optdata = optdata.append("int_16_t " + list[1] + "(){\n");
                        else if (list[3] == "32")
                            optdata = optdata.append("int_32_t " + list[1] + "(){\n");
                        else if (list[3] == "64")
                            optdata = optdata.append("int_64_t " + list[1] + "(){\n");
                    }
                    else if (list[4] == "f") {
                        if (list[3] == "16")
                            optdata = optdata.append("int_fast16_t " + list[1] + "(){\n");
                        else if (list[3] == "32")
                            optdata = optdata.append("int_fast32_t " + list[1] + "(){\n");
                        else if (list[3] == "64")
                            optdata = optdata.append("int_fast64_t " + list[1] + "(){\n");
                    }
                }
                else if (list[2] == "void") {
                    optdata = optdata.append("void " + list[1] + "(){\n");
                }
                else if (list[2] == "char")
                    optdata = optdata.append("char " + list[1] + "(){\n");
                else if (list[2] == "float") {
                    optdata = optdata.append("float " + list[1] + "(){\n");
                }
                else if (list[2] == "double") {
                    optdata = optdata.append("double " + list[1] + "(){\n");
                }
                else if (list[2] == "bool")
                    optdata = optdata.append("bool " + list[1] + "(){\n");
                else if (list[2] == "string")
                    optdata = optdata.append("std::string " + list[1] + "(){\n");
                else if (list[2] == "long")
                    optdata = optdata.append("long " + list[1] + "(){\n");
                else if (list[2] == "szt")
                    optdata = optdata.append("size_t " + list[1] + "(){\n");
            }
            else if (list[0] == "for")
                optdata = optdata.append("\tfor(){\n\t\t\n}");
            else if (list[0] == "if")
                optdata = optdata.append("\tif(){\n\t\t\n}");
            else if (list[0] == "elf")
                optdata = optdata.append("\telse if(){\n\t\t\n}");
            else if (list[0] == "els")
                optdata = optdata.append("\telse{\n\t\t\n}");
            else if (list[0] == "whl")
                optdata = optdata.append("\twhile(){\n\t\t\n}");
            else if (list[0] == "strswc")
                optdata = optdata.append("\tswitch(){\n");
            else if (list[0] == "case")
                optdata = optdata.append("\t\tcase " + list[1] + ":\n\t\t\t\n\t\t\tbreak;\n");
            else if (list[0] == "dflt")
                optdata = optdata.append("\t\tdefault:\n\t\t\t\n\t\t\tbreak;\n");
            else if (list[0] == "endswc")
                optdata = optdata.append("\t}\n");
            else if (list[0] == "endfunc_nms")
                optdata = optdata.append("}\n");
            else if (list[0]=="ret")
                optdata = optdata.append("\treturn " + list[1] + ";\n");
			else if (list[0] == "inc")
				optdata = optdata.append("#include <" + list[1] + ">\n");
            else if (list[0]=="strnms")
                optdata = optdata.append("namespace " + list[1] + " {\n");
            stream << file.error();
            stream << optfl.error();
            stream << file.errorString();
            stream << optfl.errorString();
            //stream << "//error below if found";
            stream.flush();

        }
    }
    else if (arg1 == "-jv") {
        while (true) {
            QString str = QString(file.readLine(1024));
            str = str.trimmed();
            QStringList list = str.split(" ");
            if (list[0] == "end") {
                break;
            }
            if (list[0] == "strcls") {
                if (list[2]=="n")
                    optdata = optdata.append("class " + list[1] + " {\n");
                else if (list[2]=="c")
                    optdata = optdata.append("class " + list[1] + " {\n\tpublic " + list[1] + "(){\n\t}\n");
            }
            else if (list[0] == "strfunc") {
                if (list[2] == "int") {
                    if  (list[3]=="pus")
                        optdata = optdata.append("\tpublic static int "+ list[1]+"(){\n");
                    else if (list[3] == "prvs")
                        optdata = optdata.append("\tprivate static int " + list[1] + "(){\n");
					else if (list[3] == "prots")
						optdata = optdata.append("\tprotected static int " + list[1] + "(){\n");
                    if (list[3] == "pu")
                        optdata = optdata.append("\tpublic int " + list[1] + "(){\n");
                    else if (list[3] == "prv")
                        optdata = optdata.append("\tprivate int " + list[1] + "(){\n");
                    else if (list[3] == "prot")
                        optdata = optdata.append("\tprotected int " + list[1] + "(){\n");
                }
                else if (list[2] == "void") {
					if (list[3] == "pus")
						optdata = optdata.append("\tpublic static void " + list[1] + "(){\n");
					else if (list[3] == "prvs")
						optdata = optdata.append("\tprivate static void " + list[1] + "(){\n");
					else if (list[3] == "prots")
						optdata = optdata.append("\tprotected static void " + list[1] + "(){\n");
					if (list[3] == "pu")
						optdata = optdata.append("\tpublic void " + list[1] + "(){\n");
					else if (list[3] == "prv")
						optdata = optdata.append("\tprivate void " + list[1] + "(){\n");
					else if (list[3] == "prot")
						optdata = optdata.append("\tprotected void " + list[1] + "(){\n");
				}
                else if (list[2] == "float") {
					if (list[3] == "pus")
						optdata = optdata.append("\tpublic static float " + list[1] + "(){\n");
					else if (list[3] == "prvs")
						optdata = optdata.append("\tprivate static float " + list[1] + "(){\n");
					else if (list[3] == "prots")
						optdata = optdata.append("\tprotected static float " + list[1] + "(){\n");
					if (list[3] == "pu")
						optdata = optdata.append("\tpublic float " + list[1] + "(){\n");
					else if (list[3] == "prv")
						optdata = optdata.append("\tprivate float " + list[1] + "(){\n");
					else if (list[3] == "prot")
						optdata = optdata.append("\tprotected float " + list[1] + "(){\n");
				}
                else if (list[2] == "double") {
                    if (list[3] == "pus")
                        optdata = optdata.append("\tpublic static double " + list[1] + "(){\n");
                    else if (list[3] == "prvs")
                        optdata = optdata.append("\tprivate static double " + list[1] + "(){\n");
                    else if (list[3] == "prots")
                        optdata = optdata.append("\tprotected static double " + list[1] + "(){\n");
                    if (list[3] == "pu")
                        optdata = optdata.append("\tpublic double " + list[1] + "(){\n");
                    else if (list[3] == "prv")
                        optdata = optdata.append("\tprivate double " + list[1] + "(){\n");
                    else if (list[3] == "prot")
                        optdata = optdata.append("\tprotected double " + list[1] + "(){\n");
                }
                else if (list[2] == "bool") {
                    if (list[3] == "pus")
                        optdata = optdata.append("\tpublic static boolean " + list[1] + "(){\n");
                    else if (list[3] == "prvs")
                        optdata = optdata.append("\tprivate static boolean " + list[1] + "(){\n");
                    else if (list[3] == "prots")
                        optdata = optdata.append("\tprotected static boolean " + list[1] + "(){\n");
                    if (list[3] == "pu")
                        optdata = optdata.append("\tpublic boolean " + list[1] + "(){\n");
                    else if (list[3] == "prv")
                        optdata = optdata.append("\tprivate boolean " + list[1] + "(){\n");
                    else if (list[3] == "prot")
                        optdata = optdata.append("\tprotected boolean " + list[1] + "(){\n");
                }
                else if (list[2] == "string") {
                    if (list[3] == "pus")
                        optdata = optdata.append("\tpublic static String " + list[1] + "(){\n");
                    else if (list[3] == "prvs")
                        optdata = optdata.append("\tprivate static String " + list[1] + "(){\n");
                    else if (list[3] == "prots")
                        optdata = optdata.append("\tprotected static String " + list[1] + "(){\n");
                    if (list[3] == "pu")
                        optdata = optdata.append("\tpublic String " + list[1] + "(){\n");
                    else if (list[3] == "prv")
                        optdata = optdata.append("\tprivate String " + list[1] + "(){\n");
                    else if (list[3] == "prot")
                        optdata = optdata.append("\tprotected String " + list[1] + "(){\n");
                }
                else if (list[2] == "char") {
                    if (list[3] == "pus")
                        optdata = optdata.append("\tpublic static char " + list[1] + "(){\n");
                    else if (list[3] == "prvs")
                        optdata = optdata.append("\tprivate static char " + list[1] + "(){\n");
                    else if (list[3] == "prots")
                        optdata = optdata.append("\tprotected static char " + list[1] + "(){\n");
                    if (list[3] == "pu")
                        optdata = optdata.append("\tpublic char " + list[1] + "(){\n");
                    else if (list[3] == "prv")
                        optdata = optdata.append("\tprivate char " + list[1] + "(){\n");
                    else if (list[3] == "prot")
                        optdata = optdata.append("\tprotected char " + list[1] + "(){\n");
                }
            }
            else if (list[0] == "for")
                optdata = optdata.append("\t\tfor(){\n\t\t\n}");
            else if (list[0] == "if")
                optdata = optdata.append("\t\tif(){\n\t\t\n}");
            else if (list[0] == "elf")
                optdata = optdata.append("\t\telse if(){\n\t\t\n}");
            else if (list[0] == "els")
                optdata = optdata.append("\t\telse{\n\t\t\n}");
            else if (list[0] == "whl")
                optdata = optdata.append("\t\twhile(){\n\t\t\n}");
            else if (list[0] == "strswc")
                optdata = optdata.append("\t\tswitch(){\n");
            else if (list[0] == "case")
                optdata = optdata.append("\t\t\tcase " + list[1] + ":\n\t\t\t\t\n\t\t\t\tbreak;\n");
            else if (list[0] == "dflt")
                optdata = optdata.append("\t\t\tdefault:\n\t\t\t\t\n\t\t\t\tbreak;\n");
            else if (list[0] == "endswc")
                optdata = optdata.append("\t\t}\n");
            else if (list[0] == "endfunc")
                optdata = optdata.append("\t}\n");
            else if (list[0] == "ret")
                optdata = optdata.append("\t\treturn " + list[1] + ";\n");
            else if (list[0] == "imp")
                optdata = optdata.append("import " + list[1] + ";\n");
            else if (list[0]=="endcls")
                optdata = optdata.append("}\n");
            else if (list[0]=="pkg")
                optdata = optdata.append("package " + list[1] + ";\n");
            stream << file.error();
            stream << optfl.error();
            stream << file.errorString();
            stream << optfl.errorString();
            //stream << "//error below if found";
            stream.flush();
        }
    }
    optfl.write(optdata.toUtf8());
    file.close();
    optfl.close();
    QCoreApplication::exit();
    exit(0);
    return a.exec();
}
