<?xml version="1.0" encoding="ISO-8859-1"?>

<xsl:stylesheet version="2.0" id="fr0-cumulate-count-plus"
                xmlns:xsd="http://www.w3.org/2001/XMLSchema"
                xmlns:xsl="http://www.w3.org/1999/XSL/Transform"
                exclude-result-prefixes="xsd">

  <xsl:output method="text"/>

  <xsl:strip-space elements="*"/>

  <xsl:variable name="eol" select="'&#10;'"/>

  <xsl:template match="poemefr1">
    <xsl:apply-templates select="corps"/>
  </xsl:template>

  <xsl:template match="corps">
    <xsl:apply-templates select="ligne[@strophe='oui'][position()!=1]"/>
    <xsl:value-of select="count(ligne), $eol"
                  separator=""/>
  </xsl:template>

  <xsl:template match="ligne">
    <xsl:value-of select="count(preceding-sibling::ligne), $eol" separator=""/>
  </xsl:template>

</xsl:stylesheet>
