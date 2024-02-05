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
