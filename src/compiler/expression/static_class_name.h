/*
   +----------------------------------------------------------------------+
   | HipHop for PHP                                                       |
   +----------------------------------------------------------------------+
   | Copyright (c) 2010 Facebook, Inc. (http://www.facebook.com)          |
   +----------------------------------------------------------------------+
   | This source file is subject to version 3.01 of the PHP license,      |
   | that is bundled with this package in the file LICENSE, and is        |
   | available through the world-wide-web at the following url:           |
   | http://www.php.net/license/3_01.txt                                  |
   | If you did not receive a copy of the PHP license and are unable to   |
   | obtain it through the world-wide-web, please send a note to          |
   | license@php.net so we can mail you a copy immediately.               |
   +----------------------------------------------------------------------+
*/

#ifndef __STATIC_CLASS_NAME_H__
#define __STATIC_CLASS_NAME_H__

#include <compiler/expression/expression.h>

namespace HPHP {
///////////////////////////////////////////////////////////////////////////////

class StaticClassName {
public:
  StaticClassName(ExpressionPtr classExp);

  bool isSelf() const { return m_self; }
  bool isParent() const { return m_parent; }
  bool isStatic() const { return m_static; }
  bool isRedeclared() const { return m_redeclared; }
  bool isPresent() const { return m_present || m_forcePresent; }
  bool isUnknown() const { return m_unknown; }

  void setPresent() { m_present = m_forcePresent = true; }

  void setRedeclared() { m_redeclared = true; }

  void resolveStatic(const std::string &name);

  const std::string &getOriginalClassName() const { return m_origClassName; }
  const std::string &getClassName() const { return m_className; }
  ExpressionPtr getClass() const { return m_class; }

  ClassScopePtr resolveClass();
  bool checkPresent();
protected:
  ExpressionPtr m_class;
  std::string m_origClassName;
  std::string m_className;

  void updateClassName();
  void outputPHP(CodeGenerator &cg, AnalysisResultPtr ar);
private:
  virtual void dummyForDynamicCast() {}
  unsigned m_self : 1;
  unsigned m_parent : 1;
  unsigned m_static : 1;
  unsigned m_redeclared : 1;
  unsigned m_present : 1;
  unsigned m_forcePresent : 1;
  unsigned m_unknown : 1;
};

///////////////////////////////////////////////////////////////////////////////
}
#endif // __STATIC_CLASS_NAME_H__
