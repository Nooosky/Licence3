<?xml version="1.0" encoding="ISO-8859-1"?>

<xsl:stylesheet version="2.0" id="fr1-count-plus"
                xmlns:xsd="http://www.w3.org/2001/XMLSchema"
                xmlns:xsl="http://www.w3.org/1999/XSL/Transform"
                exclude-result-prefixes="xsd">

  <xsl:output method="text"/>

  <xsl:strip-space elements="*"/>

  <xsl:variable name="eol" select="'&#10;'"/>

  <xsl:template match="poemefr1" as="xsd:string">
    <xsl:value-of
      select="'Le nombre de strophes est : ',count(corps/ligne[@strophe='oui']),$eol"
      separator=""/>
  </xsl:template>

  <xsl:template match="poemefr1" as="xsd:string">
    <xsl:apply-templates select="corps/ligne[@strophe='oui'][position() gt 1]">
  </xsl:template>

</xsl:stylesheet>
