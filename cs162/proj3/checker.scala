import scala.io._
import cs162.assign3.syntax._
import Aliases._
import scala.io.Source.fromFile

//—————————————————————————————————————————————————————————————————————————
// Main entry point

object Checker {
  type TypeEnv = scala.collection.immutable.HashMap[Var, Type]
  object Illtyped extends Exception

  var typeDefs = Set[TypeDef]()

  def main( args:Array[String] ) {
    val filename = args(0)
    val input = fromFile(filename).mkString
    Parsers.program.run(input, filename) match {
      case Left(e) => println(e)
      case Right(program) =>
        val prettied = Pretty.prettySyntax(program)
        typeDefs = program.typedefs

        try {
          getType( program.e, new TypeEnv())
          println("This program is well-typed:\n")
          println(Pretty.prettySyntax(program))
        } catch { case Illtyped => println("This program is ill-typed") }
    }
  }

  // Gets all the constructors associated with a given type name.
  // For example, consider the following typedefs:
  //
  // type Either = Left num | Right bool
  // type Maybe = Some num | None
  //
  // With respect to the above typedefs, `constructors` will return
  // the following underneath the given arguments:
  //
  // constructors(Label("Either")) = Map(Label("Left") -> NumT, Label("Right") -> BoolT)
  // constructors(Label("Maybe")) = Map(Label("Some") -> NumT, Label("None") -> UnitT)
  // constructors(Label("Fake")) throws Illtyped
  //
  def constructors(name: Label): Map[Label, Type] =
    typeDefs.find(_.name == name).map(_.constructors).getOrElse(throw Illtyped)

  // Gets the type of the constructor.
  // For example, considering the typedefs given in the `constructors` comment above,
  // `typename` will return the following with the given arguments:
  //
  // typename(Label("Left")) = Label("Either")
  // typename(Label("Right")) = Label("Either")
  // typename(Label("Some")) = Label("Maybe")
  // typename(Label("None")) = Label("Maybe")
  //
  def typename(constructor: Label): Label =
    typeDefs.find(_.constructors.contains(constructor)).getOrElse(throw Illtyped).name

  def getType( e:Exp, env:TypeEnv ): Type =
    e match {
      // variables
      case x:Var =>  {
		  if (env contains x) env(x) 
		  else {throw Illtyped}
	  }// FILL ME IN

      // numeric literals
      case _:Num => NumT // FILL ME IN

      // boolean literals
      case _:Bool => BoolT // FILL ME IN

      // `nil` - the literal for unit
      case _: NilExp => UnitT // FILL ME IN

      // builtin arithmetic operators
      case Plus | Minus | Times | Divide => NumT // FILL ME IN

      // builtin relational operators
      case LT | EQ => BoolT // FILL ME IN

      // builtin logical operators
      case And | Or => BoolT // FILL ME IN

      // builtin logical operators
      case Not => BoolT // FILL ME IN

      // function creation
      case Fun(params, body) => {
	    var newEnv = env
		for (p <- params) {newEnv += p._1 -> p._2}
	    val ret = getType(body, newEnv)
		FunT(params.map(_._2),ret)
	  } // FILL ME IN

      // function call
      case Call(fun, args) => {
	    getType(fun, env) match {
		  case FunT(x,y)  => {

		    if (x == args.map(getType(_,env))) y
			else throw Illtyped
		  }
		  case NumT => NumT
		  case BoolT => BoolT
		  case _ => throw Illtyped
		}
	  } // FILL ME IN

      // conditionals 
      case If(e1, e2, e3) => {
	    getType(e1,env) match {
		  case BoolT => {}
		  case _ => throw Illtyped
		}
		
		val t= getType(e2,env)
		if (t == getType(e3,env)) t
		else throw Illtyped
		
	  } // FILL ME IN

      // let binding
      case Let(x, e1, e2) => getType(e2,env + (x -> getType(e1,env))) // FILL ME IN

      // recursive binding
      case Rec(x, t1, e1, e2) => {
	    if (getType(e1,env+ (x -> t1)) == t1) getType(e2,env + (x -> t1))
		else throw Illtyped
	  } // FILL ME IN

      // record literals
      case Record(fields) => RcdT(fields.map{case (k,v) => (k, getType(v, env))}) // FILL ME IN

      // record access
      case Access(e, field) => {
	    getType(e, env) match {
		  case RcdT(x) => x.getOrElse(field, throw Illtyped)
		  case _ => throw Illtyped
		}
	  } // FILL ME IN

      // constructor use
      case Construct(constructor, e) => {
	    val n = typename(constructor)
	    if (constructors(n)(constructor) == getType(e, env)) TypT(n)
		else throw Illtyped
	  } // FILL ME IN

      // pattern matching (case ... of ...)
      case Match(e, cases) => {
	    
	    getType(e, env) match {
		  case TypT(t) => {
		    
		    if ( constructors(t).size != cases.length || constructors(t).keys != cases.map(_._1).toSet) throw Illtyped

			
			val ziped = cases.zip( for (c <- cases) yield constructors(t)(c._1) )
			
			val ret = getType(ziped.head._1._3,env + (ziped.head._1._2 -> ziped.head._2))
			
			
			for (hehe <- ziped) {
		      if (ret !=  getType(hehe._1._3,env + (hehe._1._2 -> hehe._2))) throw Illtyped
		    }
			
			
			ret
		  }
		  case _ => throw Illtyped
		}

	  
	  } // FILL ME IN
    }
}
