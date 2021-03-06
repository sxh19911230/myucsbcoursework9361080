import scala.io._
import cs162.assign4.syntax._
import Aliases._
import scala.io.Source.fromFile

//——————————————————————————————————————————————————————————————————————————————
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
          println(Pretty.prettySyntax(program))
          getType( program.e, new TypeEnv())
          println("This program is well-typed")
        } catch { case Illtyped => println("This program is ill-typed") }
    }
  }

  // Gets a listing of the constructor names associated with a given type definition.
  // For example, consider the following type definition:
  //
  // type Either['A, 'B] = Left 'A | Right 'B
  //
  // Some example calls to `constructors`, along with return values:
  //
  // constructors("Either") = Set("Left", "Right")
  // constructors("Foo") = a thrown Illtyped exception
  //
  def constructors(name: Label): Set[Label] =
    typeDefs.find(_.name == name).map(_.constructors.keySet).getOrElse(throw Illtyped)

  // Takes the following parameters:
  // -The name of a user-defined type
  // -The name of a user-defined constructor in that user-defined type
  // -The types which we wish to apply to the constructor
  // Returns the type that is held within the constructor.
  //
  // For example, consider the following type definition:
  //
  // type Either['A, 'B] = Left 'A | Right 'B
  //
  // Some example calls to `constructorType`, along with return values:
  //
  // constructorType("Either", "Left", Seq(NumT, BoolT)) = NumT
  // constructorType("Either", "Right", Seq(NumT, BoolT)) = BoolT
  // constructorType("Either", "Left", Seq(NumT)) = a thrown Illtyped exception
  // constructorType("Either", "Right", Seq(BoolT)) = a thrown Illtyped exception
  // constructorType("Either", "Foo", Seq(UnitT)) = a thrown Illtyped exception
  // constructorType("Bar", "Left", Seq(UnitT)) = a thrown Illtyped exception
  //
  def constructorType(name: Label, constructor: Label, types: Seq[Type]): Type = 
    (for {
      td <- typeDefs
      rawType <- td.constructors.get(constructor)
      if (types.size == td.tvars.size)
    } yield replace(rawType, td.tvars.zip(types).toMap)).headOption.getOrElse(throw Illtyped)

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

  // Given a type and a mapping of type variables to other types, it
  // will recursively replace the type variables in `t` with the
  // types in `tv2t`, if possible.  If a type variable isn't
  // in `tv2t`, it should simply return the original type.  If a
  // `TFunT` is encountered, then whatever type variables it defines
  // (the first parameter in the `TFunT`) should overwrite whatever is in
  // `tv2t` right before a recursive `replace` call.  In other words,
  // type variables can shadow other type variables.
  //
  def replace( t:Type, tv2t:Map[TVar, Type] ): Type =
    t match {
      case NumT | BoolT | UnitT => t // FILL ME IN

      case FunT(params, ret) => {
	    FunT(for(x<-params) yield replace(x,tv2t), replace(ret,tv2t))
	  } // FILL ME IN

      case RcdT(fields) => {
	    RcdT(fields.map(x=>(x._1->replace(x._2,tv2t))))
	  } // FILL ME IN

      case TypT(name, typs) => {
	    TypT(name, typs.map(replace(_,tv2t)))
	  } // FILL ME IN

      case tv:TVar => {
	    if (tv2t contains tv) tv2t(tv) 
		else tv
	  }// FILL ME IN

      case TFunT(tvars, funt) => {
		FunT(funt.params.map(replace(_,tv2t)), replace(funt.ret,tv2t))
	  } // FILL ME IN
    }

  // HINT - the bulk of this remains unchanged from the previous assignment.
  // Feel free to copy and paste code from your last submission into here.
  def getType( e:Exp, env:TypeEnv ): Type =
    e match {
      case x:Var => {
		  //println(1)
		  if (env contains x) env(x) 
		  else {throw Illtyped}
	  }// FILL ME IN

      case _:Num => NumT // FILL ME IN

      case _:Bool => BoolT // FILL ME IN

      case _:Unit => UnitT // FILL ME IN

      case Plus | Minus | Times | Divide => NumT // FILL ME IN

      case LT | EQ => BoolT // FILL ME IN

      case And | Or => BoolT // FILL ME IN

      case Not => BoolT // FILL ME IN

      case Fun(params, body) => {
	    //println(2)
	    var newEnv = env
		for (p <- params) {newEnv += p._1 -> p._2}
	    val ret = getType(body, newEnv)
		FunT(params.map(_._2),ret)
	  } // FILL ME IN

      case Call(fun, args) => {
	  //println(3)
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

      case If(e1, e2, e3) => {
	  //println(4)
	    getType(e1,env) match {
		  case BoolT => {}
		  case _ => throw Illtyped
		}
		
		val t= getType(e2,env)
		if (t == getType(e3,env)) t
		else throw Illtyped
		
	  } // FILL ME IN
		
      case Let(x, e1, e2) => getType(e2,env + (x -> getType(e1,env)))// FILL ME IN

      case Rec(x, t1, e1, e2) => {
	  //println(5)
	    if (getType(e1,env+ (x -> t1)) == t1) getType(e2,env + (x -> t1))
		else throw Illtyped
	  } // FILL ME IN

      case Record(fields) => {
	    //println(6);
	    RcdT(fields.map{case (k,v) => (k, getType(v, env))})
	  } // FILL ME IN

      case Access(e, field) => {
	  //println(7)
	    getType(e, env) match {
		  case RcdT(x) => x.getOrElse(field, throw Illtyped)
		  case _ => throw Illtyped
		}
	  } // FILL ME IN

      case c @ Construct(constructor, typs, e) => {
	  //println(8)
	    val n = typename(constructor)
		
		//println(typs)
		//println(constructor)
		//println(constructorType(n,constructor,typs))
		//println(getType(e, env))
		
	    if (constructorType(n,constructor,typs) == getType(e, env)) TypT(n,typs)
		else throw Illtyped
	  } // FILL ME IN

      case Match(e, cases) => {
	  //println(9)
	    
	    getType(e, env) match {
		  case TypT(t,types) => {
		    if ( constructors(t).size != cases.length || constructors(t) != cases.map(_._1).toSet) throw Illtyped

			val ziped = cases.zip( for (c <- cases) yield constructorType(t,c._1,types) )
			
			val ret = getType(ziped.head._1._3,env + (ziped.head._1._2 -> ziped.head._2))
			
			for (hehe <- ziped) {
		      if (ret !=  getType(hehe._1._3,env + (hehe._1._2 -> hehe._2))) throw Illtyped
		    }
			
			ret
		  }
		  case _ => {
		    throw Illtyped
		  }
		}

	  
	  } // FILL ME IN

      case TAbs(tvars, fun) => {
	  //println(10)
	      TFunT(tvars,FunT(fun.params.map(_._2),getType(fun.body,env++fun.params.map(tmp=>(tmp._1->tmp._2)))))
		}// FILL ME IN

      case TApp(e, typs) => {
	  //println(11)
	    getType(e,env) match {
		  case tf:TFunT => {
		    val t = replace (tf, (tf.tvars zip typs) toMap)
			//println(t)
			t
		  }
		  case _ => throw Illtyped
		}
	  } // FILL ME IN
    }
}
