<?xml version="1.0" encoding="ISO-8859-1"?>

<xsl:stylesheet version="2.0" id="books-1"
                xmlns:xsd="http://www.w3.org/2001/XMLSchema"
                xmlns:xsl="http://www.w3.org/1999/XSL/Transform"
                exclude-result-prefixes="xsd">

  <xsl:output method="text"/>

  <xsl:strip-space elements="*"/>

  <xsl:variable name="eol" select="'&#10;'"/>

  <xsl:template match="sf-1">
    <xsl:apply-templates select="entries"/>
  </xsl:template>

  <xsl:template match="entries">
    <xsl:apply-templates select="book">
      <!--<xsl:sort select="position()" order="descending"/>
      <xsl:sort select="id(author/personrefs/@to)[1]/last"/>
      <xsl:sort select="id(author/personrefs/@to)[1]/first"/>-->
      <xsl:sort select="title/text()"/>
    </xsl:apply-templates>
  </xsl:template>

  <xsl:template match="book">
    <xsl:apply-templates select="id(author/personrefs/@to)"/>
    <xsl:value-of select="normalize-space(title/string()), $eol" separator=""/>
    <xsl:value-of select="publisher, ' , ' , year , ' . ', $eol" separator=""/>
  </xsl:template>

  <xsl:template match="personname">
    <xsl:apply-templates select="first|last"/>
    <xsl:if test="position() &lt; last()">
      <xsl:text>, </xsl:text>
    </xsl:if>
  </xsl:template>


</xsl:stylesheet>
