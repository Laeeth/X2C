/*
 * attributeUse.cpp
 *
 *  Created on: 28.8.2011
 *      Author: Adam Juraszek
 */

#include "attributeUse.h"
#include "utils.h"
#include "simpleType.h"

void AttributeUse::generate(QString &className, QString &ehprivate,
		QString &ehpublic, QString &ehinclude, QString &ecpp,
		QString &eccinclude) {
	Attribute *a = getAttribute();
	SimpleType *st = a->getSimpleType();
	QString dt = st->getDataType();
	QString name = unqualify(a->getName());
	ehpublic.append("bool " + methodName(name, "has") + "() {\n");
	ehpublic.append("  return " + varName(name, "has", "Value") + ";\n");
	ehpublic.append("}\n");
	qDebug() <<dt;
	ehpublic.append(dt + " " + methodName(name, "get") + "() {\n");
	ehpublic.append("  return " + varName(name, QString(), "Value") + ";\n");
	ehpublic.append("}\n");

	ehprivate.append(dt + " " + varName(name, QString(), "Value") + ";\n");
	ehprivate.append("bool " + varName(name, "has", "Value") + ";\n");
	ehprivate.append("void " + methodName(name, "set") + "(QString string);\n");
	ehprivate.append("void " + methodName(name, "init") + "();\n");

	ecpp.append(
			"void " + className + "::" + methodName(name, "set")
					+ "(QString string) {\n");
	ecpp.append("  " + varName(name, QString(), "Value") + " = string;\n");
	ecpp.append("}\n");

	ecpp.append(
			"void " + className + "::" + methodName(name, "init") + "(){\n");
	ecpp.append(
			"  qDebug() << \"" + className + "\"<<\"" + name
					+ "\" <<\"init\";\n");
	ecpp.append(
			"  " + varName(name, QString(), "Value") + " = " + dt + "();\n");
	ecpp.append("}\n");

}
