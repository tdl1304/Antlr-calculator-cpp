// Generated from C:/Users/tommy/CLionProjects/ExprMain\Expr.g4 by ANTLR 4.9.1
import org.antlr.v4.runtime.tree.ParseTreeListener;

/**
 * This interface defines a complete listener for a parse tree produced by
 * {@link ExprParser}.
 */
public interface ExprListener extends ParseTreeListener {
	/**
	 * Enter a parse tree produced by {@link ExprParser#prog}.
	 * @param ctx the parse tree
	 */
	void enterProg(ExprParser.ProgContext ctx);
	/**
	 * Exit a parse tree produced by {@link ExprParser#prog}.
	 * @param ctx the parse tree
	 */
	void exitProg(ExprParser.ProgContext ctx);
	/**
	 * Enter a parse tree produced by {@link ExprParser#expr}.
	 * @param ctx the parse tree
	 */
	void enterExpr(ExprParser.ExprContext ctx);
	/**
	 * Exit a parse tree produced by {@link ExprParser#expr}.
	 * @param ctx the parse tree
	 */
	void exitExpr(ExprParser.ExprContext ctx);
	/**
	 * Enter a parse tree produced by {@link ExprParser#neg}.
	 * @param ctx the parse tree
	 */
	void enterNeg(ExprParser.NegContext ctx);
	/**
	 * Exit a parse tree produced by {@link ExprParser#neg}.
	 * @param ctx the parse tree
	 */
	void exitNeg(ExprParser.NegContext ctx);
	/**
	 * Enter a parse tree produced by {@link ExprParser#assn}.
	 * @param ctx the parse tree
	 */
	void enterAssn(ExprParser.AssnContext ctx);
	/**
	 * Exit a parse tree produced by {@link ExprParser#assn}.
	 * @param ctx the parse tree
	 */
	void exitAssn(ExprParser.AssnContext ctx);
	/**
	 * Enter a parse tree produced by {@link ExprParser#num}.
	 * @param ctx the parse tree
	 */
	void enterNum(ExprParser.NumContext ctx);
	/**
	 * Exit a parse tree produced by {@link ExprParser#num}.
	 * @param ctx the parse tree
	 */
	void exitNum(ExprParser.NumContext ctx);
}